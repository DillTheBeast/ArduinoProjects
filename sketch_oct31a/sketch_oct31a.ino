// #include <Servo.h>

// Servo myServo;  // create servo object to control a servo

// void setup() {
//   myServo.attach(3);  // attaches the servo on pin 3 to the servo object
// }

// void loop() {   
//   for(int i = 0; i < 360; i++) {
//     myServo.write(i);
//   }   
// } 

#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(3);  // attaches the servo on pin 3 to the servo object
}

void loop() {
  myServo.write(0);   // rotate in one direction continuously
  // You don't need any delay here if you just want it to keep rotating in one direction
}
