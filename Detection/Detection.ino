#include <Servo.h>

#define SERVO_PIN     9  //servo connect to D9

#define EchoF 2 // Ultrasonic Echo pin connect to D11
#define TrigF 10  // Ultrasonic Trig pin connect to D12

#define speedPinR 3   // RIGHT PWM pin connect MODEL-X ENA
#define RightDirectPin1  12    //  Right Motor direction pin 1 to MODEL-X IN1 
#define RightDirectPin2  11    // Right Motor direction pin 2 to MODEL-X IN2
#define speedPinL 6        //  Left PWM pin connect MODEL-X ENB
#define LeftDirectPin1  7    // Left Motor direction pin 1 to MODEL-X IN3
#define LeftDirectPin2  8   ///Left Motor direction pin 1 to MODEL-X IN4
#define LPT 2 // scan loop coumter

#define FAST_SPEED  250     //both sides of the motor speed
#define SPEED  120     //both sides of the motor speed
#define TURN_SPEED  200     //both sides of the motor speed
#define BACK_SPEED1  255     //back speed
#define BACK_SPEED2  90     //back speed

Servo head;
long distance, duration, FrontSensor;

void setup() {
  // put your setup code here, to run once:
  pinMode(TrigF, OUTPUT);
  pinMode(EchoF, INPUT);
  head.attach(SERVO_PIN); 
  //88 = middle for servo facing forward
  head.write(87);
  Serial.begin(9600);
}
void detection(int trig) {
  
  int bestDistance = 0;
  int bestAngle = 0;
    for(int i = 177; i >= -13; i-=50) {
      Serial.println(i);
      if(i == -13) 
        i = 7;

      else if(i == 127)
        i = 137;

      head.write(i);

      delay(200);
      SonarSensor(TrigF, EchoF);
      FrontSensor = distance;
      if(distance > bestDistance) {
        bestDistance = distance;
        bestAngle = i;
      }
    }
    if(bestAngle == 177) {
      //Full Left
      go_Left(75);
      delay(400);
      stop_Stop();
      head.write(87);
    }
    else if(bestAngle == 137) {
      //Half Left
      go_Left(75);
      delay(100);
      stop_Stop();
      head.write(87);
    }
    else if(bestAngle == 27) {
      //Half Right
      go_Right(75);
      delay(100);
      stop_Stop();
      head.write(87);
    }
    else if(bestAngle == 7) {
      //Full Right
      go_Right(75);
      delay(400);
      stop_Stop();
      head.write(87);
    }
    else {
      //Straight forward
      head.write(87);
    }
    while(FrontSensor > 20 || FrontSensor == 0) {
      SonarSensor(TrigF, EchoF);
      FrontSensor = distance;
      go_Advance(75);
    }
    stop_Stop();
    return;
  
}
void SonarSensor(int trigPin,int echoPin) {
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
  detection(TrigF);
}
void go_Advance(int t) {
  //Forward
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,255);
  analogWrite(speedPinR,255);
  delay(t);
}
void go_Left(int t) {
  //Turn left
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
  delay(t);
}
void go_Right(int t) {
  //Turn right
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  analogWrite(speedPinL,200);
  analogWrite(speedPinR,200);
  delay(t);
}
void go_Back(int t) {
  //Reverse
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  analogWrite(speedPinL,255);
  analogWrite(speedPinR,255);
  delay(t);
}
void stop_Stop() {
  //Stop
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,LOW);
}