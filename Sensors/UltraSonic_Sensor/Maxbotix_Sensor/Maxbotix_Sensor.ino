// Arduino synth library absolute frequency example

//Hardware connections:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND


#include <synth.h>

synth cymaticTone;    //-Make a synth

const int anPin1 = 0;
long dist;

int controlData;
int maxThresh = 75;
int minThresh = 0;

void setup() {

  Serial.begin(9600);
  
  //Synth//
  
  cymaticTone.begin();                                   //-Start it up
  cymaticTone.setupVoice(0,TRIANGLE,60,ENVELOPE1,127,64);  //-Set up voice 0
  cymaticTone.trigger(0);

  
}

void loop()
{  
  
  int freq = map(controlData, 0, maxThresh, 40, 0);
  
  cymaticTone.setFrequency(0, freq);

  read_sensors();
  print_all();
  delay(50); 
 
}

void read_sensors(){
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  dist = analogRead(anPin1)/2;

   if (dist >= maxThresh || dist <= minThresh) {

        controlData = maxThresh;
      
      } else {
        
        controlData = dist;
      }
}


void print_all(){
  
  Serial.print("Inches: ");
  Serial.print(dist);
  Serial.println();
  
}









