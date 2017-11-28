$fn = 200;

difference(){
    cube([50,20,0.8]);
    translate([9,10,-1]){
        cylinder(5,1.2,1.2);
    }
    translate([17,10,-1]){
        cylinder(5,1.2,1.2);
    }
}

difference(){
    translate([17,10,0]){
        cylinder(3,1.8,1.8);
    }
    translate([17,10,-1]){
        cylinder(5,1.2,1.2);
    }
}

difference(){
    translate([9,10,0]){
        cylinder(3,1.8,1.8);
    }
    translate([9,10,-1]){
        cylinder(5,1.2,1.2);
    }
}