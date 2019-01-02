float incrementalAngle = 0.0;

void setup(){
    size(600, 600);
    smooth();
    background(0);
    
    ellipse(width/2, height/2, 200, 200);
    drawCircles(20, 200);
}

void drawCircles(int circlesNumber, int bigCircleNumber){
    float angle = incrementalAngle;
    
    for(int i = 0; i < circlesNumber; i++){
        ellipse(bigCircleNumber * cos(incrementalAngle) + height/2,
                bigCircleNumber * sin(incrementalAngle) + width/2,
                circlesNumber, circlesNumber);
        incrementalAngle += TWO_PI / circlesNumber;
    } 
}