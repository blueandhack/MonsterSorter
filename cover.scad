$fn = 200;

difference(){
    difference(){
        cylinder(10, 56, 56);
        translate([0,0,-1]){
            cylinder(9, 52, 52);
        }
    }
    translate([-6,-5,4]){
        cube([12.2,23.2,10]);
    }
    translate([0,-7.3,4]){
        cylinder(8, 1.0, 1.0);
    }
    translate([0,20,4]){
        cylinder(8, 1.0, 1.0);
    }
    
    translate([0,-30,4]){
        cylinder(8, 15, 20);
    }
}


translate([51,-2,0]){
    cube([2,4,4]);
}

translate([-53,-2,0]){
    cube([2,4,4]);
}

translate([-2,-53,0]){
    cube([4,2,4]);
}

translate([-2,51,0]){
    cube([4,2,4]);
}

a = 1.1;
b = 2.5;