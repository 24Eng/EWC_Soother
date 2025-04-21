thickness = 1.75;
knobDiameter = 40.0;
knobHeight = 15.00;
knobBubbleDiameter = 2;
bubbleCount = 20;
encoderShaftDiameter = 5.85;
encoderShaftDepth = 10;
encoderFlatFromSide = 4.40;
roundedEdgeRadius = 1;


// 24 Eng // 24 Eng // 24 Eng // 24 Eng // 24 Eng // 24 Eng // 24 Eng
knobRadius = knobDiameter/2;
encoderShaftRadius = encoderShaftDiameter/2;
encoderFlatFromCenter = encoderFlatFromSide - encoderShaftRadius;
echo("encoderFlatFromCenter ", encoderFlatFromCenter);
knobBubbleRadius = knobBubbleDiameter/2;
bubbleAngle = 360 / bubbleCount;
echo("bubbleAngle", bubbleAngle);

$fn = 36;
//$vpr = [-20,$t*360 + 70,0];
//$vpt = [0,-2,knobHeight/2];

// Create the post that encompasses the encoder shaft
difference(){
    cylinder(encoderShaftDepth+thickness, encoderShaftRadius + thickness, encoderShaftRadius + thickness);
    translate([0,0,thickness+0.01]){
        difference(){
            cylinder(encoderShaftDepth, encoderShaftRadius, encoderShaftRadius);
            translate([encoderShaftRadius*2 + encoderFlatFromCenter,0,encoderShaftDepth/2])cube([encoderShaftRadius*4, encoderShaftRadius*4, encoderShaftDepth*2], center = true);
        }
    }
}

// Create the top
translate([0,0,roundedEdgeRadius]){
    minkowski(){
        cylinder(thickness, knobRadius-knobBubbleRadius-roundedEdgeRadius, knobRadius-  knobBubbleRadius-roundedEdgeRadius);
        sphere(roundedEdgeRadius);
    }
}

// Make the crenulated edges
for (i = [0: bubbleAngle: 360-bubbleAngle]){
    rotate([0,0,i]){
        translate([0,knobRadius-knobBubbleRadius,roundedEdgeRadius*1.5]){
            minkowski(){
                cylinder(knobHeight-roundedEdgeRadius*2.5, 0.01, 0.01);
                sphere(roundedEdgeRadius);
            }
        }
    }
}
translate([0,0,roundedEdgeRadius]){
    difference(){
        cylinder(knobHeight-roundedEdgeRadius, knobRadius-knobBubbleRadius, knobRadius-knobBubbleRadius);
        cylinder(knobHeight*2, knobRadius-knobBubbleRadius-thickness, knobRadius-knobBubbleRadius-thickness, center=true);
    }
}