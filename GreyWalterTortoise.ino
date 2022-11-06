#include <Servo.h> 
Servo servoLeft;
Servo servoRight;

double leftAmb;
double rightAmb;

void setup() {
servoLeft.attach(13);         
servoRight.attach(12);

//since my whiskers dont work i chose random pins
pinMode(5, INPUT); // left whisker
pinMode(6, INPUT); // right whisker

//declaring Detector variables
double lIrDetector;
double rIrDetector;

Serial.begin(9600);

//for loop to get ambient ambient light and calibrate
for (int i=0; i<11; i++) {
  maneuver(200,50,10);
  //since I dont have photo transistors or capacitors i chose random analog pins
  lIrDetector += analogRead(A2);
  rIrDetector += analogRead(A1);
  delay(1000);
}
//calibrating to ambient light 
maneuver(0,0,10);
leftAmb = (lIrDetector/10)*0.95;
rightAmb =(rIrDetector/10)*0.95;

}

void loop() {
  //Whisker setup
  byte left = digitalRead(5);
byte right = digitalRead(6);
  if (left == 0 && right == 1) {
    // -- left touch, right not    
    maneuver(-200,-50,1);
    delay(1000);
  }
  else if (left == 1 && right == 0) {
    // -- left not, right touch
    maneuver(-50,-200,1);
    delay(1000);   
  }
  else if (left == 0 && right == 0) {
    // -- left touch, right touch
    maneuver(-200,-200,1);
    delay(1000); 
  }
  
  //assigning Pin's to variables 
double lAdc = analogRead(A2);
double rAdc = analogRead(A1);


//"maping" the servo's to light intensity
double leftSpeed = map(lAdc, leftAmb,1023,0,200);
double rightSpeed = map(rAdc, rightAmb,1023,0,200);
  maneuver(rightSpeed, leftSpeed, 1);
  
Serial.println(left);
Serial.println(right);
}
void maneuver(float speedLeft, float speedRight, int msTime) {
  servoLeft.writeMicroseconds(1500 + speedLeft); // Left servo speed 
  servoRight.writeMicroseconds(1500 - speedRight); // Right servo speed 
  if(msTime==-1) // if msTime = -1
    { 
      servoLeft.detach();
      servoRight.detach();// Stop servo signals
    }
    delay(msTime);   
}
