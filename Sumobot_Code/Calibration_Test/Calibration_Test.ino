#include <Servo.h> 

Servo servoR;
Servo servoL;

int pos = 0;

void setup() 
{ 
  servoR.attach(4);
  servoL.attach(2);
  servoL.write(90);  // set servo to mid-point (90)
  servoR.write(90); 
} 

void loop() {} 
