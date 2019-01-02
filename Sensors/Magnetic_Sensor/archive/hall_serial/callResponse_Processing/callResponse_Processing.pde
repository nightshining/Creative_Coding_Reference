// This example code is in the public domain.

import processing.serial.*;

Serial myPort;                       // The serial port
int[] serialInArray = new int[4];    // Where we'll put what we receive
int serialCount = 0;                 // A count of how many bytes we receive
boolean firstContact = false;        // Whether we've heard from the microcontroller

void setup() {
  size(256, 256);  
  noStroke();     
  println(Serial.list());
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(255);
}

void serialEvent(Serial myPort) {
  int inByte = myPort.read();
  if (firstContact == false) {
    if (inByte == 'A') {
      myPort.clear();          // clear the serial port buffer
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write('A');       // ask for more
    }
  }
  else {
    serialInArray[serialCount] = inByte;
    serialCount++;
    if (serialCount > 3 ) {
      for (int i=0; i<4; i++) {
        print(serialInArray[i]);
        print("\t");
      }
      println();
      myPort.write('z');
      serialCount = 0;
    }
  }
}
