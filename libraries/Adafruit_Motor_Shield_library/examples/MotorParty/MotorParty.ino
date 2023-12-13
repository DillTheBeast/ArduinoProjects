//WIRED

#include <AlignedJoy.h>

#include <Keyboard.h>

#include <AFMotor.h>
#include <Servo.h>

#define VRX_PIN 18  // Arduino pin connected to VRX pin
#define VRY_PIN 19  // Arduino pin connected to VRY pin

#define xHigh 10
#define xLow -10
#define yHigh 10
#define yLow -10

int xValue = 0;  // To store value of the X axis
int yValue = 0;  // To store value of the Y axis

// DC motor on M2
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
// DC hobby servo
Servo servo1;

void setup() {
  Serial.begin(9600);  // set up Serial library at 9600 bps
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
}

// Test the DC motor, stepper and servo ALL AT ONCE!
void loop() {
  int direction = FORWARD;
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  yValue -= 512;
  yValue = yValue / 2;
  direction = (yValue < 0 ? BACKWARD : FORWARD);

  if (yValue < 0 && yValue > -10) {
    yValue = 0;
  }
  if (yValue == -256) {
    yValue = -255;
  }

  Serial.print("x: ");
  Serial.print(xValue);
  Serial.print(", y: ");
  Serial.print(yValue);

  Serial.println("");

  if (xValue < 500) {
    //moveForward(200);
    moveForward(200);
  } else if (yValue > 50 && yValue < 70) {
    moveLeft(200);
  } else if (yValue == -255) {
    moveRight(200);
  } else if (xValue > 700) {
    //left
    moveBackward(200);
  } else {
    moveForward(0);
  }

  delay(5);
}

void moveForward(int speed) {
  Serial.print("test");
  motor1.setSpeed(speed);
  motor1.run(FORWARD);
  delay(1);
  motor2.setSpeed(speed);
  motor2.run(FORWARD);
  delay(1);
  motor3.setSpeed(speed);
  motor3.run(FORWARD);
  delay(1);
  motor4.setSpeed(speed);
  motor4.run(FORWARD);
  delay(1);
}
void moveBackward(int speed) {
  motor1.setSpeed(speed);
  motor1.run(BACKWARD);
  delay(1);
  motor2.setSpeed(speed);
  motor2.run(BACKWARD);
  delay(1);
  motor3.setSpeed(speed);
  motor3.run(BACKWARD);
  delay(1);
  motor4.setSpeed(speed);
  motor4.run(BACKWARD);
  delay(1);
}
void moveRight(int speed) {
  motor1.setSpeed(speed);
  motor1.run(FORWARD);
  delay(1);
  motor2.setSpeed(speed);
  motor2.run(FORWARD);
  delay(1);
  motor3.setSpeed(speed);
  motor3.run(BACKWARD);
  delay(1);
  motor4.setSpeed(speed);
  motor4.run(BACKWARD);
  delay(1);
}
void moveLeft(int speed) {
  motor1.setSpeed(speed);
  motor1.run(BACKWARD);
  motor2.setSpeed(speed);
  motor2.run(BACKWARD);
  motor3.setSpeed(speed);
  motor3.run(FORWARD);
  delay(1);
  motor4.setSpeed(speed);
  motor4.run(FORWARD);
  delay(1);
}