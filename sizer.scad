$fn = 200;


difference(){
    cube([20,20,32]);
    translate([10,10,-2]){
        // cube([16,16,45]);
        cylinder(50,7,7);
    }
    translate([2,-1,10]){
        cube([25,35,2]);
    }
    translate([2,-1,22]){
        cube([25,35,2]);
    }
    translate([-1,2,13]){
        cube([5,15,8]);
    }
}

//color("red") translate([2,-18,31]){
//        cube([25,50,2]);
//}
//
//color("blue") translate([2,-1,11]){
//        cube([25,50,2]);
//}

difference(){
    translate([10,10,31]){
        cylinder(12,10,10);
    }
    translate([10,10,30]){
        cylinder(20,7,7);
    }
}

difference(){
    translate([10,10,-11]){
        cylinder(12,10,10);
    }
    translate([10,10,-12]){
        cylinder(20,7,7);
    }
}

difference(){
    translate([-6,0,5]){
        cube([6,20,25]);
    }
    translate([-4,-1,7]){
        cube([4,22,21]);
    }
}

translate([-4,0,7]){
    cube([4,3,1]);
}

translate([-4,17,7]){
    cube([4,3,1]);
}