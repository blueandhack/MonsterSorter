#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

// Example code for the Adafruit TCS34725 breakout library applied to Skittle colour classification.
// This example uses RGB vectors for classification.  It also converts the RGB vector to a HSB colourspace, 
// which is likely more robust for this classification, but does not implement the HSB classification.
// (If you change to HSB, you will likely only need hue and saturation, and not brightness). 

// More information:
// Breakout board: https://www.adafruit.com/product/1334
// Library: https://github.com/adafruit/Adafruit_TCS34725
// Installation instructions: https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/how-to-install-a-library

   
// Initialise TCS24725 with specific int time and gain values 
// Note: 2-4 millisecond integration (sampling) times mean we can sample at about 250-500Hz
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

/*
 * Global colour sensing variables
 */

#define NUM_COLORS  6

// Skittle colours to indices
#define COL_RED     0
#define COL_GREEN   1
#define COL_ORANGE  2
#define COL_YELLOW  3
#define COL_PURPLE  4
#define COL_NOTHING 5

// Names for colours
#define COLNAME_RED     "RED"
#define COLNAME_GREEN   "GREEN"
#define COLNAME_ORANGE  "ORANGE"
#define COLNAME_YELLOW  "YELLOW"
#define COLNAME_PURPLE  "PURPLE"
#define COLNAME_NOTHING "NOTHING"

// RGB channels in the array
#define CHANNEL_R   0
#define CHANNEL_G   1
#define CHANNEL_B   2

// Training colours (populate these manually, but these vectors must be of unit length (i.e. length 1))
float trainingColors[3][NUM_COLORS];    // 3(rgb) x NUM_COLORS.

// Last read colour
float rNorm = 0.0f;
float gNorm = 0.0f;
float bNorm = 0.0f;
float hue = 0.0f;
float saturation = 0.0f;
float brightness = 0.0f;

// Last classified class
int lastClass = -1;
float lastCosine = 0;


// servo
Servo servo1;
Servo servo2;
Servo servo3;
int buttonServo = 11;
int topServo = 9;
int selectServo = 4;

/*
 * Colour sensing
 */
void initializeTrainingColors() {
  // Skittle: red
  trainingColors[CHANNEL_R][COL_RED] = 0.567;
  trainingColors[CHANNEL_G][COL_RED] = 0.621;
  trainingColors[CHANNEL_B][COL_RED] = 0.540;

  // Skittle: green
  trainingColors[CHANNEL_R][COL_GREEN] = 0.445;
  trainingColors[CHANNEL_G][COL_GREEN] = 0.735;
  trainingColors[CHANNEL_B][COL_GREEN] = 0.512;

  // Skittle: orange
  trainingColors[CHANNEL_R][COL_ORANGE] = 0.681;
  trainingColors[CHANNEL_G][COL_ORANGE] = 0.570;
  trainingColors[CHANNEL_B][COL_ORANGE] = 0.460;

  // Skittle: yellow
  trainingColors[CHANNEL_R][COL_YELLOW] = 0.611;
  trainingColors[CHANNEL_G][COL_YELLOW] = 0.669;
  trainingColors[CHANNEL_B][COL_YELLOW] = 0.422;

  // Skittle: purple
  trainingColors[CHANNEL_R][COL_PURPLE] = 0.484;
  trainingColors[CHANNEL_G][COL_PURPLE] = 0.645;
  trainingColors[CHANNEL_B][COL_PURPLE] = 0.591;

  // Nothing
  trainingColors[CHANNEL_R][COL_NOTHING] = 0.448;
  trainingColors[CHANNEL_G][COL_NOTHING] = 0.665;
  trainingColors[CHANNEL_B][COL_NOTHING] = 0.605;
}


void getNormalizedColor() {
  uint16_t r, g, b, c, colorTemp, lux;  
  tcs.getRawData(&r, &g, &b, &c);

  float lenVec = sqrt((float)r*(float)r + (float)g*(float)g + (float)b*(float)b);

  // Note: the Arduino only has 2k of RAM, so rNorm/gNorm/bNorm are global variables. 
  rNorm = (float)r/lenVec;
  gNorm = (float)g/lenVec;
  bNorm = (float)b/lenVec;

  // Also convert to HSB:
  RGBtoHSV(rNorm, gNorm, bNorm, &hue, &saturation, &brightness);
}


int getColorClass() {
  float distances[NUM_COLORS] = {0.0f};

  // Step 1: Compute the cosine similarity between the query vector and all the training colours. 
  for (int i=0; i<NUM_COLORS; i++) {
    // For normalized (unit length) vectors, the cosine similarity is the same as the dot product of the two vectors.
    float cosineSimilarity = rNorm*trainingColors[CHANNEL_R][i] + gNorm*trainingColors[CHANNEL_G][i] + bNorm*trainingColors[CHANNEL_B][i];
    distances[i] = cosineSimilarity;

    // DEBUG: Output cosines
    Serial.print("   C"); Serial.print(i); Serial.print(": "); Serial.println(cosineSimilarity, 3);
  }

  // Step 2: Find the vector with the highest cosine (meaning, the closest to the training color)
  float maxVal = distances[0];
  int maxIdx = 0;
  for (int i=0; i<NUM_COLORS; i++) {
    if (distances[i] > maxVal) {
      maxVal = distances[i];
      maxIdx = i;
    }
  }

  // Step 3: Return the index of the minimum color
  lastCosine = maxVal;
  lastClass = maxIdx;
  return maxIdx;
}


// Convert from colour index to colour name.
void printColourName(int colIdx) {
  switch (colIdx) {
    case COL_RED:
      Serial.print(COLNAME_RED);
      break;
    case COL_GREEN:
      Serial.print(COLNAME_GREEN);
      break;
    case COL_ORANGE:
      Serial.print(COLNAME_ORANGE);
      break;
    case COL_YELLOW:
      Serial.print(COLNAME_YELLOW);
      break;
    case COL_PURPLE:
      Serial.print(COLNAME_PURPLE);
      break;
    case COL_NOTHING:
      Serial.print(COLNAME_NOTHING);
      break;
    default:
      Serial.print("ERROR");
      break;
  }
}

/*
 * Colour converstion
 */

// RGB to HSV.  From https://www.cs.rit.edu/~ncs/color/t_convert.html . 
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v ) {  
  float minVal = min(min(r, g), b);
  float maxVal = max(max(r, g), b);
  *v = maxVal;       // v
  float delta = maxVal - minVal;
  if( maxVal != 0 )
    *s = delta / maxVal;   // s
  else {
    // r = g = b = 0    // s = 0, v is undefined
    *s = 0;
    *h = -1;
    return;
  }
  if( r == maxVal )
    *h = ( g - b ) / delta;   // between yellow & magenta
  else if( g == maxVal )
    *h = 2 + ( b - r ) / delta; // between cyan & yellow
  else
    *h = 4 + ( r - g ) / delta; // between magenta & cyan
  *h *= 60;       // degrees
  if( *h < 0 )
    *h += 360;
}


/*
 * Main Arduino functions
 */
 
void setup(void) {
  Serial.begin(115200);

  // Populate array of training colours for classification. 
  initializeTrainingColors();
  
  if (tcs.begin()) {
    Serial.println("Found sensor");\
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // servo part
  servo1.attach(buttonServo);
  servo2.attach(topServo);
  servo3.attach(selectServo);
  
  
  // Now we're ready to get readings!
}

void loop(void) {
  servo1.write(81);
  servo2.write(155);
  delay(300);
  servo2.write(125);
  
  delay(100);
  // Step 1: Get normalized colour vector
  getNormalizedColor();
  int colClass = getColorClass();   
  switch (colClass) {
    case COL_RED:
      servo3.write(108);
      break;
    case COL_GREEN:
      servo3.write(137);
      break;
    case COL_ORANGE:
      servo3.write(55);
      break;
    case COL_YELLOW:
      servo3.write(85);
      break;
    case COL_PURPLE:
      servo3.write(155);
      break;
    case COL_NOTHING:
      servo3.write(155);
      break;
    default:
      Serial.print("ERROR");
      break;
  }


  // Step 2: Output colour
  Serial.print("R: "); Serial.print(rNorm, 3); Serial.print("  ");
  Serial.print("G: "); Serial.print(gNorm, 3); Serial.print("  ");
  Serial.print("B: "); Serial.print(bNorm, 3); Serial.print("  ");  
  Serial.print("H: "); Serial.print(hue, 3); Serial.print("  ");
  Serial.print("S: "); Serial.print(saturation, 3); Serial.print("  ");
  Serial.print("B: "); Serial.print(brightness, 3); Serial.print("  ");
  
  printColourName(colClass);  
  
  
  Serial.print(" (cos: "); Serial.print(lastCosine); Serial.print(") ");
  Serial.println("");
  servo1.write(110);
  
  //servo3.write(100);
  
  delay(200);

}
