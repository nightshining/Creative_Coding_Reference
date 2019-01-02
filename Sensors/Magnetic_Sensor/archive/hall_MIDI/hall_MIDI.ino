// Pin Assignments
byte leds[] = {0, 1, 2, 3};
byte hallSensors[] = {A8, A7, A6, A5};

// Threshold and Trigger Variables
int triggerThreshold = 490;
int retriggerThreshold = 510;
boolean triggerStates[4];

void setup() {
  for (int i=0; i<4; i++) pinMode(leds[i], OUTPUT);
}

void loop() {
  // Collect Readings and Determine Trigger States
  for (int i=0; i<4; i++) {
    int reading = analogRead(hallSensors[i]);   
    if (reading < triggerThreshold && triggerStates[i] == false) {
      triggerStates[i] = true;
      digitalWrite(leds[i], HIGH);
      usbMIDI.sendNoteOn(48+i, 127, 1);
    }
    if (reading > retriggerThreshold && triggerStates[i] == true) {
      triggerStates[i] = false;
      digitalWrite(leds[i], LOW);
      usbMIDI.sendNoteOff(48+i, 0, 1);
    }
  }
}
