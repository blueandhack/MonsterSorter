$fn = 200;

// blender

translate([-16.5,0,25]){
    cube([25,2,30]);
}
difference(){
    difference(){
        translate([0,0,0]){
            cube([48,2,72]);
        }
        translate([-3.5,-1,0]){
            rotate([0,25,0]){
                cube([50,4,150]);
            }
        }
    }
    difference(){
    translate([-0.01,-1,25]){
        cube([48,4,72]);
    }
    translate([9,-1,25]){
        rotate([0,25,0]){
            cube([40,4,150]);
        }
    }
}
}