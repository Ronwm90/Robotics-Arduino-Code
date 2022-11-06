#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
 //Speaker sound for 1 second
tone(4, 2000, 1);
 servoLeft.attach(12);
 servoRight.attach(13);
 pinMode(1, OUTPUT);
 pinMode(2, OUTPUT);
 
 Serial.begin(9600);
 

 
  // put your setup code here, to run once:

}

void loop() {
  //reading analog circuits for phototransistor
double left = analogRead(A0);
double right = analogRead(A1);
double shaded;


shaded = right / (left + right) -0.5;

  if (shaded > .01){
    //When both LED's find light it moves forward with both lights on
    digitalWrite(1, HIGH);
    digitalWrite(2, HIGH);
    maneuver(200, 200, 0);
  }else{
    //With no light everything turns off
     digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    maneuver(0, 0, 0);
  }

  if (shaded > .01){
    //Robot move to the left with corresponding LED 
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    maneuver(-200, 200, 0);
  }else if (shaded <  .01){
    //Robot moves to the right with corresponding LED 
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    maneuver(200, -200, 0);
}

}
//Manuever function
void maneuver(int speedLeft, int speedRight, int msTime)
{
servoLeft.writeMicroseconds(1500 + speedLeft);
servoRight.writeMicroseconds(1500 - speedRight);
if(msTime == -1){
  servoLeft.detach();
  servoRight.detach();
  }
  delay(msTime);

}
