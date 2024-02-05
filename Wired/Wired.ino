//WIRED

#define MOTOR12_64KHZ _BV(CS00)  // no prescale
#define STEPPER1_PWM_RATE MOTOR12_64KHZ


#include <AlignedJoy.h>

#include <Keyboard.h>

#include <AFMotor.h>
#include <Servo.h>

#define FAST_SPEED  250
#define SPEED  120
#define TURN_SPEED  200
#define BACK_SPEED1  255
#define BACK_SPEED2  90

#define speedPinR 3
#define RightDirectPin1  12
#define RightDirectPin2  11
#define speedPinL 6
#define LeftDirectPin1  7
#define LeftDirectPin2  8
#define LPT 2

#define VRX_PIN 15
#define VRY_PIN 19

#define xHigh 14
#define xLow -10
#define yHigh 5
#define yLow -15

int xValue = 0;
int yValue = 0;


void setup() {
  Serial.begin(9600);

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
}

void loop() {
  //Turn the outputs of the joycon in between -100 and 100
  int xValue = map(analogRead(VRX_PIN), 0, 1023, -100, 100); 
  int yValue = map(analogRead(VRY_PIN), 0, 1023, -100, 100);

//Find out where the user wants to move
  if(yValue < yHigh && yValue > yLow && xValue < xHigh && xValue > xLow) {
    stop_Stop();
    Serial.println("No");
  }
  else if(yValue < yLow) {
  //Runs if need to move backwards
  go_Back(abs(yValue * 2.55));
  Serial.println("Backward");
  }
  else if(xValue > xHigh) {
  //Runs if need to move right/left
  go_Right(abs(xValue * 2.55));
  Serial.println("Right");
  }
  else if(yValue > yHigh) {
    go_Advance(abs(yValue * 2.55));
    Serial.println("Forward");
  }
  else if(xValue < xLow) {
    //Runs if need to move right/left
    go_Left(abs(xValue * 2.55));
    Serial.println("Left");
  }
  delay(5);
}
//Function to move in each direction
void go_Advance(int t)  //Forward
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,t);
  analogWrite(speedPinR,t);
}
void go_Left(int t)  //Turn left
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,t);
  analogWrite(speedPinR,t);
}
void go_Right(int t)  //Turn right
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,t);
  analogWrite(speedPinR,t);
}
void go_Back(int t)  //Reverse
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,t);
  analogWrite(speedPinR,t);
}
void stop_Stop()    //Stop
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,LOW);
}