#include <Servo.h>

Servo servo;
#define SERVO_PIN 11  //servo connect to D9


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(170);
  delay(100000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
