int radius = 5;
float r=20, a=0;

void setup(){
  size(400,400);
  background(0);
  smooth();
  stroke(255);
}


void draw(){
  float x=r*cos(a);
  float y=r*sin(a);
  ellipse(width/2+x,height/2+y,radius,radius);
  a=a+map(mouseY,0,height,0.0,1.0);
  r=r+map(mouseX,0,width,0.0,1.0);
}