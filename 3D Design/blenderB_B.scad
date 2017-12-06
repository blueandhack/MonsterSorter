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
    translate([0,0,-1]){
        cylinder(11,2.5,2.5);
    }
}