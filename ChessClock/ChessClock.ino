#include <TM1637Display.h>

unsigned long startTime = 0;
unsigned long elapsedTime = 0;
boolean blackTime = false;

const int buttonPin = 2;
const int ledPin = 13;

/*
#define CLK1 3
#define DIO1 4
#define CLK2 9
#define DIO2 10

TM1637Display display1 = TM1637Display(CLK1, DIO1);
TM1637Display display2 = TM1637Display(CLK2, DIO2);
*/

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as INPUT with internal pull-up resistor
  pinMode(ledPin, OUTPUT);  // Set the LED pin as OUTPUT
}

void loop() {
  //Find out which side it is on
  int buttonState = digitalRead(buttonPin);

  // Check if the button is pressed and the timer is not running
  if (buttonState == LOW && !timerRunning) {
    // Start the timer
    startTime = millis();
    timerRunning = true;
  }

  // Check if the button is pressed and the timer is running
  if (buttonState == LOW && timerRunning) {
    // Stop the timer
    timerRunning = false;
    elapsedTime = 0;
    digitalWrite(ledPin, LOW);  // Turn off the LED
  }

  // Check if the timer is running
  if (timerRunning) {
    // Calculate the elapsed time
    elapsedTime = millis() - startTime;

    // Check if 5 seconds have passed
    if (elapsedTime >= 5000) {
      // Stop the timer
      timerRunning = false;
      elapsedTime = 0;
      digitalWrite(ledPin, LOW);  // Turn off the LED
    }

    // Update the LED based on the timer state
    if (timerRunning) {
      digitalWrite(ledPin, HIGH);  // Turn on the LED
    } else {
      digitalWrite(ledPin, LOW);  // Turn off the LED
    }
}