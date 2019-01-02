  #include <CapacitiveSensor.h>
  
  /*
   * CapitiveSense Library Demo Sketch
   * Paul Badger 2008
   * Uses a high value resistor e.g. 10M between send pin and receive pin
   * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
   * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   */
  
  
  CapacitiveSensor   cs_4_3 = CapacitiveSensor(6,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

  long maxRead;
  long minRead;
  long preValue;
  long numSamples;
  long prevYreading;
  long currYreading;
  void setup()                    
  {
     cs_4_3.set_CS_AutocaL_Millis(10000);
     //Mouse.begin();
     Serial.begin(9600);
     maxRead = -2000000;
     minRead = 10000000;
     numSamples = 10;
  }
  
  void loop()                    
  {
    long total1 =  cs_4_3.capacitiveSensor(numSamples);
    maxRead = max(maxRead, total1);
    minRead = min(minRead, total1);
    currYreading = map(total1, minRead, maxRead, 0, 1000);
 
    long yReading = prevYreading - currYreading;
    prevYreading = currYreading;
    Serial.print(currYreading);
    Serial.write("\n");
    delay(1);
  }
