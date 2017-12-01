h = 50;
size = 39.8;

// bottom
difference(){
    cube([size,size,h]);
    translate([2,2,2]){
        cube([36,36,h]);
    }
}

// baffle
bh = 30;
translate([0,0,h]){
    cube([2,size,bh]);
}