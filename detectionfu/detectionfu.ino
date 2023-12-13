#include <Servo.h>

#define SERVO_PIN     9  //servo connect to D9

#define EchoF 2 // Ultrasonic Echo pin connect to D11
#define TrigF 10  // Ultrasonic Trig pin connect to D12

Servo head;
long distance, duration, FrontSensor;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(TrigF, OUTPUT);
  pinMode(EchoF, INPUT);
  head.attach(SERVO_PIN); 
  head.write(0);
  Serial.begin(9600);
}
void detection(int trig) {
  if(FrontSensor > 30 || FrontSensor == 0) {
    Serial.println(i);
    i = 0;
    head.write(0);
  }
  else {
    i+=10;
    head.write(i);
  }
}
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}

void loop() {
  // put your main code here, to run repeatedly:
  SonarSensor(TrigF, EchoF);
  FrontSensor = distance;
  detection(TrigF);
}
void go_Advance(int t = 0)  //Forward
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,255);
  analogWrite(speedPinR,255);
  delay(t);
}
void go_Left(int t=0)  //Turn left
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
  delay(t);
}
void go_Right(int t=0)  //Turn right
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
  delay(t);
}
void go_Back(int t=0)  //Reverse
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,255);
  analogWrite(speedPinR,255);
  delay(t);
}
void stop_Stop()    //Stop
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,LOW);
}
