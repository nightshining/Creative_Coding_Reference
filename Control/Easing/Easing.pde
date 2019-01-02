
float easeStart;
float easing; // easing percentage

void setup() {
  
  easeStart = 0.0;
  easing = 0.01;
  
}


void draw() {
  
  float val = easeStart += (mouseX - easeStart) * easing;
  
  println("Easing: " + val);
}