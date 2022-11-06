#include "Servo.h"
Servo servoLeft; // Declare left and right servos
Servo servoRight;
void setup() {
  // put your setup code here, to run once:
pinMode(7, INPUT); // left whisker
pinMode(5, INPUT); // right whisker
pinMode(3, OUTPUT); // left led
pinMode(2, OUTPUT); // right led
servoLeft.attach(13);
servoRight.attach(12);
Serial.begin(9600);
}

void loop() {
  // -- sense the environment
  int left = digitalRead(7);
  int right = digitalRead(5);

  // -- decide how to act
  if (left == 1 && right == 1) {
    // -- neither is touching 
    digitalWrite(3, LOW);  
    digitalWrite(2, LOW); 
    servoLeft.writeMicroseconds(-1600);   
    servoRight.writeMicroseconds(1600); 
    delay(500);
  }
  else if (left == 0 && right == 1) {
    // -- left touch, right not 
    digitalWrite(2, LOW);  
    digitalWrite(3, HIGH);
    servoLeft.writeMicroseconds(1600);   
    servoRight.writeMicroseconds(1500);
    tone(4, 1046, 1500);
  }
  else if (left == 1 && right == 0) {
    // -- left not, right touch
    digitalWrite(2, HIGH);  
    digitalWrite(3, LOW);
    servoLeft.writeMicroseconds(1500);   
    servoRight.writeMicroseconds(1600);
    tone(4, 2093, 1500);
  }
  else if (left == 0 && right == 0) {
    // -- left touch, right touch
    digitalWrite(3, HIGH);  
    digitalWrite(2, HIGH);
    tone(4, 4186, 1500);
  }

  // -- achieve goal
  Serial.print(left);
  Serial.print(right);
  Serial.println();
  delay(100);

   
}
