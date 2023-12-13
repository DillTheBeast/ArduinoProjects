#include <Servo.h>

const int arraySize = 5;
int commandNum[arraySize];

//Yellow = pinky
const int yLight = 3;
const int gLight = 5;
const int wLight = 6;
const int bLight = 10;
const int rLight = 11;
int lightpins[5] = {3, 5, 6, 10, 11};
char one = '1';

//Motor 11: 160 = top ; 5 = bottom
//Motor 10: 0 = top ; 160 = bottom
//Motor 6: 170 = top ; 0 = bottom
//Motor 5: 180 = top ; 0 = bottom
//Motor 3: 0 = top ; 110 = bottom

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(yLight, OUTPUT);
  pinMode(gLight, OUTPUT);
  pinMode(wLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(rLight, OUTPUT);
  delay(1);
}

/*
void flatten() {
  servos[0].write(110);
  servos[1].write(0);
  servos[2].write(0);
  servos[3].write(160);
  servos[4].write(5);
}
*/

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) {
  if(Serial.readString()) {
    digitalWrite(wLight, HIGH);
  }
  else {
    digitalWrite(rLight, HIGH);
  }
    String receivedString = Serial.readString(); // Read the incoming string
    //receivedString.trim(); // Remove any leading or trailing whitespace

    if (receivedString.length() == arraySize) {
      for (int i = 0; i < arraySize; i++) {
        char currentChar = receivedString.charAt(i);

        if (currentChar == '1') {
          commandNum[i] = 1; // Set the array element to 1 if '1' is received
          digitalWrite(bLight, HIGH);

        } else if (currentChar == '0') {
          commandNum[i] = 0; // Set the array element to 0 if '0' is received
          digitalWrite(yLight, HIGH);
        } else {
          // Handle any other character received (optional)
          digitalWrite(gLight, HIGH);
        }
      }
    }
/*
    if(commandNum[0] == 1) {
      digitalWrite(yLight, HIGH);
      Serial.println("Yellow On");
    }
    else {
      digitalWrite(yLight, LOW);
      Serial.println("Yellow Off");
    }
    if(commandNum[1] == 1) {
      digitalWrite(gLight, HIGH);
      Serial.println("Green On");
    }
    else {
      digitalWrite(gLight, LOW);
      Serial.println("Green Off");
    }
    if(commandNum[2] == 1) {
      digitalWrite(wLight, HIGH);
      Serial.println("White On");
    }
    else {
      digitalWrite(wLight, LOW);
      Serial.println("White Off");
    }
    if(commandNum[3] == 1) {
      digitalWrite(bLight, HIGH);
      Serial.println("Blue On");
    }
    else {
      digitalWrite(bLight, LOW);
      Serial.println("Blue Off");
    }
    if(commandNum[4] == 1) {
      digitalWrite(rLight, HIGH);
      Serial.println("Red On");
    }
    else {
      digitalWrite(rLight, LOW);
      Serial.println("Red Off");
    }
    */
  }
}