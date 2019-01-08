
float value, target;

void setup() {
 
  size(500,500);
  value = 0;
  target = value;
  
}

void draw() {
  
  background(255); //Make sure to background refresh!

  float offset = 0.5;
  float radius = 50;
  float speed = 0.2;
  
  value = lerp(value, target, speed);

  fill(0);
  rectMode(CENTER);
  rect(width*offset,height*offset,radius*value, radius*value);
  
  ellipse(width * 0.2, height * 0.5 * value, 50,50);

}

void keyPressed() {
 
  if (key == '1') {
   
    target = 0.25;
   
  } else if (key == '2') {
   
     target = 0.50;
     
  } else if(key == '3') {
   
     target = 1.5; 
  } else if (key == '4') {
     target = 3.0; 
  }
  
}