// Computer Science 20 - Mr. Schellenberg  - Pd. 4
// Major Project - Arduino Sumobot
// By: Sarvath Sharma
// Completed June 11, 2017

#include <Servo.h> // bring in the servo library

Servo servoR; // state the right servo variable/name
Servo servoL; // state the left servo variable/name

const int pingPin = 7; //  The pin number of the sensor output (constant number)

void setup() {
  Serial.begin(9600);
  // all the pins for the servos:
  servoR.attach(4); // The right servo is attached to PIN 4
  servoL.attach(2); // The left servo is attached to PIN 2
}

void forward() {
  // makes the Sumobot move forward
  Serial.println("FORWARD");
  servoR.write(80); // 0-90 Forward
  servoL.write(100); // 90-180 Forward
}

void forwardFast() {
  // makes the Sumobot move forward really fast
  Serial.println("SPEED");
  servoR.write(60); 
  servoL.write(120); 
}

void backward() {
  // makes the Sumobot go backwards
  Serial.println("BACKWARD");
  servoR.write(100); // 90-180 Backward
  servoL.write(80); // 0-90 Backward
}

void turnRight() {
  // the Sumobot will turn right
  Serial.println("RIGHT");
  servoR.write(90); 
  servoL.write(100);
  delay(750); // turn right for 1 second
}

void turnLeft() {
  // the Sumobot will turn left
  Serial.println("LEFT");
  servoR.write(80);
  servoL.write(90);
  delay(750); // turn left fot 1 second
}

void stopMoving() {
  // The Sumobot seizes movement
  Serial.println("STOP");
  servoR.write(90);
  servoL.write(90);
}

void slightRight() {
  // Moves but has a right curve
  Serial.println("BEND RIGHT");
  servoR.write(85);
  servoL.write(105);
  delay(200); // The left servo rotates faster to have a right curve
}

void slightLeft() {
  // Moves with a left curve
  Serial.println("BEND LEFT");
  servoR.write(75);
  servoL.write(95);
  delay(1000); // The right servo rotates faster to have a left curve
}

void attackDodge() {
  // makes the Sumobot trick attackers and dodge their incoming attacks
  Serial.println("FAKE ATTACK");
  turnRight();
  forwardFast();
  delay(500);
  turnLeft();
  forwardFast();
  delay(500);
  slightLeft();
  forwardFast();
  delay(500);
  stopMoving();
  backward();
  delay(200);
  slightRight();
  forwardFast();
  delay(200);
}

void theEyes() {
  // establish variables for duration of the ping,
  // and the distance result in centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delay(2000);
  digitalWrite(pingPin, HIGH);
  delay(5000);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  if (cm > 20) {
    forward(); // If there is an object 20cm or further away the Sumobot will move forward
  } else if (cm <= 15) {
    stopMoving(); // If there is an object 15 cm or less the Sumobot will run the attackDodge() function to fight
    backward(); // Assumes that object is wide enough to move way from
    delay(150);
    attackDodge();
  }
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void loop() {
  // make the Sumobot run various functions in a loop
  theEyes();
}

