#include <Shifter.h>

// Shift Register Variables
#define SRCLK_Pin 0 
#define RCLK_Pin 1 
#define SER_Pin 2
#define NUM_REGISTERS 1
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

// Pin Assignments
byte sensorInputs[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
byte lastLEDs[] = {3, 4, 5, 6}; // LEDs 8-11

// Trigger Variables
int triggerThreshold = 530;      // Tweak lower to increase distance from sensor for trigger to occur.
int retriggerThreshold = 515;    // Don't touch for the most part.
boolean triggerStates[12];
boolean lastStates[12];

// Serial Communication Variables
char sendOn[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
char sendOff[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};

void setup() {
  for (int i=0; i<4; i++) pinMode(lastLEDs[i], OUTPUT);
  for (int i=0; i<12; i++) lastStates[i] = false;
  
  for (int i=0; i<3; i++) {          // Start up pattern
    digitalWrite(lastLEDs[3], HIGH);
    delay(100);
    digitalWrite(lastLEDs[3], LOW);
    delay(100);
  }
}

void loop() { 
  //  Get Readings from Hall Sensors and Set Triggers
  for (int i=0; i<12; i++) {
    int reading = analogRead(sensorInputs[i]);   
    reading = constrain(reading, 0, 1023);
    if (reading > triggerThreshold && triggerStates[i] == false) {
      triggerStates[i] = true;
    }
    if (reading < retriggerThreshold && triggerStates[i] == true) {
      triggerStates[i] = false;
    }
    
    //  Keyboard Communication
    if (lastStates[i] != triggerStates[i]) {
      setPins();
      lastStates[i] = triggerStates[i];
      if (triggerStates[i] == true) Keyboard.print(sendOn[i]);
      if (triggerStates[i] == false) Keyboard.print(sendOff[i]);
    }    
  } 
}

void setPins() {
  //  Set Shift Register LEDs
  shifter.clear();
  for (int x=0; x<8; x++) shifter.setPin(x, triggerStates[x]);
  shifter.write();  

  //  Set Remaining LEDs
  for (int i=0; i<4; i++) digitalWrite(lastLEDs[i], triggerStates[i+8]);  
}
