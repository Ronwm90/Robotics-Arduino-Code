void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //initialize digitalphoto
int digitalphoto = qtTime(1);
// -- achieve goal
Serial.print("digitalphoto");
Serial.print(digitalphoto);
Serial.println();

delay(100);
}
long qtTime(int pin)
{
  // -- charge the capacitor
 pinMode(pin, OUTPUT);
 digitalWrite(pin, HIGH);
 delay(1);
// -- discharge the capacitor and read the pin
 pinMode(pin, INPUT);
 digitalWrite(pin, LOW);
 long time = micros();
 while(digitalRead(pin));
 time =micros() - time; 
 return time;
}
