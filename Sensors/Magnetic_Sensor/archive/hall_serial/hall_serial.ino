// Pin Assignments
byte leds[] = {0, 1, 2, 3};
byte hallSensors[] = {A8, A7, A6, A5};

// Threshold and Trigger Variables
int triggerThreshold = 490;
int retriggerThreshold = 510;
boolean triggerStates[4];

// Serial Communication
int inByte = 0;

void setup() {
  for (int i=0; i<4; i++) pinMode(leds[i], OUTPUT);
  Serial.begin(9600);
  establishContact();
}

void loop() {
  // Collect Readings and Determine Trigger States
  for (int i=0; i<4; i++) {
    int reading = analogRead(hallSensors[i]);   
    if (reading < triggerThreshold && triggerStates[i] == false) {
      triggerStates[i] = true;
      digitalWrite(leds[i], HIGH);
    }
    if (reading > retriggerThreshold && triggerStates[i] == true) {
      triggerStates[i] = false;
      digitalWrite(leds[i], LOW);
    }
  }

  // Send Trigger States Over Serial
  if (Serial.available() > 0) {
    inByte = Serial.read();
    for (int i=0; i<4; i++) {
      Serial.write(triggerStates[i]); 
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A'); 
    delay(300);
  }
}
