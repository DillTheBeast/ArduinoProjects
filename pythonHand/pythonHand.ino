#include <Servo.h>

const int numServos = 5;  // Define the number of servo motors you want to control
Servo servos[numServos];  // Create an array of servo objects

//Motor 11: 160 = top ; 5 = bottom
//Motor 10: 0 = top ; 160 = bottom
//Motor 6: 170 = top ; 0 = bottom
//Motor 5: 180 = top ; 0 = bottom
//Motor 3: 0 = top ; 110 = bottom

// Pins connected to servo motors
int servoPins[numServos] = {3, 5, 6, 10, 11};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Attach the servo objects to their respective pins
  for(int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
  }
  flatten();
  delay(1);
}

void flatten() {
  servos[0].write(110);
  servos[1].write(0);
  servos[2].write(0);
  servos[3].write(160);
  servos[4].write(5);
}

void loop() {
  // put your main code here, to run repeatedly:
 // if(Serial.available() > 0) {
    //byte data = Serial.read();
    byte data = 0b10101010;
    Serial.println(data);
    //first = thumb, last = pinky
    for(int i = 0; i < 8; i++) { 
      byte mask = 1<<i;
      Serial.println(mask, BIN);
      Serial.println(data & mask, BIN);
      if ((data & mask) == mask ) servos[i].write(180);
      else servos[i].write(0);
      delay(500);
      // if (bitRead(data, i) == 1) {
      //   if(i == 0) {
      //     servos[0].write(0);
      //   }
      //   else if(i == 1) {
      //     servos[1].write(180);
      //   }
      //   else if(i == 2) {
      //     servos[2].write(170);
      //   }
      //   else if(i == 3) {
      //     servos[3].write(0);
      //   }
      //   else if(i == 4) {
      //     servos[4].write(160);
      //   }
      // }
      // else {
      //   if(i == 0) {
      //     servos[0].write(110);
      //   }
      //   else if(i == 1) {
      //     servos[1].write(0);
      //   }
      //   else if(i == 2) {
      //     servos[2].write(0);
      //   }
      //   else if(i == 3) {
      //     servos[3].write(160);
      //   }
      //   else if(i == 4) {
      //     servos[4].write(5);
      //   }
      // }
    //}
  }
}