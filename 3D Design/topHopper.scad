$fn = 200;

translate([0,0,12]){
    difference(){
        cylinder(90, 9, 52);
        translate([0,0,-1]){
            cylinder(92, 7, 50);
        }
    }
}

difference(){
    cylinder(18,12.5,12.5);
    translate([0,0,-1]){
        cylinder(28,10,10);
    }
}

translate([0,0,10]){
    difference(){
        cylinder(2,11,11);
        translate([0,0,-1]){
            cylinder(7,7,7);
        }
    }
}