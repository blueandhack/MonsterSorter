$fn = 200;

difference(){
    difference(){
        cylinder(10, 56, 56);
        translate([0,0,-1]){
            cylinder(9, 52, 52);
        }
    }
    translate([0,0,7]){
        cylinder(8, 2.5, 2.5);
    }
    translate([7.5,0,7]){
        cylinder(8, 2, 2);
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