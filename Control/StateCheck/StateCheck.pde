
boolean state;

void setup() {
  
  state = false;
}

void draw() {
  float normalMouse = norm(mouseX, 0, width);
  boolean val = stateCheck(normalMouse, 0.5);
  println("State: " + val ); 

}

boolean stateCheck(float input, float thresh) {
  
    boolean toggle = false;
  
  if (state == false) {
   
    if (input > thresh) {
      
        toggle = true;
        state = !state;
    }  
    
  }
  
  if (state == true) {
    
    if (input < thresh) {
      
      toggle = false;
      state = !state;
    }
    
  }
  
  return toggle;
}