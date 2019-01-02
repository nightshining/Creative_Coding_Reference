const int pwPin1 = 3;
long sensor, mm, inches;

void setup() {
Serial.begin(9600);
pinMode(pwPin1, INPUT); }

void read_sensor (){
sensor = pulseIn(pwPin1, HIGH);
mm = sensor;
inches = mm/25.4;
}

void print_range(){

  /*
   * 
   * Serial Output Format
The sensor output is provided over the COM port (or equivalent) in an ASCII character format. If a target is detected at
480 millimeters the output appears as follows: “R0480 <carriage return>“. The output is an ASCII capital “R”, followed
by four ASCII character digits representing the range in millimeters up to a maximum of 5000 millimeters. This is
followed by an ASCII space and a carriage return.
   */

long mmMax = min(mm/10,5000);
String mmStr = String(mmMax);
while(mmStr.length()<4){
  mmStr = "0"+mmStr;
}
String str ="R"+ mmStr +"\n";

Serial.print(str);
/*Serial.print("S1");
Serial.print("=");
Serial.print(mm);
Serial.print(" mm, ");
Serial.println(inches);
Serial.print(" in \n");*/
}

void loop() { read_sensor();
print_range();
delay(100);
}
