
float angle;
int speed;
int radius;
float x, y;

void setup() {
  
  size(320,240);
  smooth();
  speed = 100;
  radius = 100;
}


void draw() {
  background(255);
  
  float inc = angle;
  angle += TWO_PI / speed;

  x = radius * cos(inc) + width * 0.5f;
  y = radius * sin(inc) + height * 0.5f;
 
  fill(0);
  ellipse(x,y,15,15);
 
}