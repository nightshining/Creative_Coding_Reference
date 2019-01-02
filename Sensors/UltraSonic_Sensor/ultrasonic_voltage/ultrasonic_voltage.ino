const int anPin = 0;
long anVolt, mm, inches;

void setup() {
Serial.begin(9600);
}

void read_sensor(){
anVolt = analogRead(anPin);
mm = anVolt * 5;
inches = mm/25.4;
}

void print_range(){
Serial.print("S1");
Serial.print("=");
Serial.print(mm);
Serial.print(" ");
Serial.println(inches);
}

void loop() {
read_sensor();
print_range();
delay(100);
}
