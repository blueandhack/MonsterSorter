$fn = 200;

difference(){
    translate([0,0,0]){
        cylinder(4,15,15);
    }
    translate([0,10,-1]){
        cylinder(10,1,1);
    }
    translate([0,-10,-1]){
        cylinder(10,1,1);
    }
    translate([-16.5,-3.5,-1]){
        cube([33,7,3]);
    }
    translate([]){
        cylinder(10,3.5,3.5);
    }
}