h = 50;
size = 59;
w = 79;
// bottom
difference(){
    cube([size,w,h]);
    translate([2,2,2]){
        cube([size-4,w-4,h]);
    }
}

// baffle
bh = 40;
translate([0,0,h]){
    cube([2,w,bh]);
}