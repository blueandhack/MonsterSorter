$fn = 200;

// blender
difference(){
    translate([0,0,25]){
        cube([48,2,72]);
    }
    translate([8,-1,25]){
        rotate([0,25,0]){
            cube([40,4,150]);
        }
    }
}


difference(){
    translate([0,0,95]){
        cylinder(2,15,15);
    }
    translate([0,10,93]){
        cylinder(5,1,1);
    }
    translate([0,-10,93]){
        cylinder(5,1,1);
    }
}

translate([-6,-2,92]){
    cube([20,6,5]);
}