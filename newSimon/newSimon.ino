#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <fonts/FreeSansBold24pt7b.h>

#define RED     11    
#define YELLOW  10
#define BLUE     9
#define GREEN    8

#define BTN_R   7
#define BTN_Y   6
#define BTN_B   5
#define BTN_G   4

#define PHOTOR  14

String pattern = "";        // This variable is where the randomly generated pattern will be stored
int score = 0;              // This variable stores your current score 
int count = 0;              // This variable keeps track of where in the sequence the player is while repeating the pattern
bool waiting = false;       // This variable tracks whether the game is playing a sequence or waiting for the player to complete the last sequence

void setup() {
  //Set pin modes
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_Y, INPUT_PULLUP);
  pinMode(BTN_G, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);

  pinMode(PHOTOR, INPUT);
  Serial.begin(9600);
  //Boot up test sequence lights all LEDs sequentially
  showRed();
  delay(150);
  showYellow();
  delay(150);
  showBlue();
  delay(150);
  showGreen();
  delay(150);
  //end
  
  setSequence();    //Randomly generate a pattern
}

void setSequence() {

  // First we need to seed our random number generator with a truly random number
  randomSeed(analogRead(14));

  // This generates a 100-character String that consists of randomly selected letters corresponding to the 4 colors
  for (int i = 0; i < 100; i++) {
    int ran = random(0,4); 
    if (ran == 1) pattern+='B';
    else if (ran == 2) pattern+='G';
    else if (ran == 3) pattern+='R';
    else pattern+='Y';
  }

  Serial.println(pattern);
  
}

void loop() {
  // Turn off all lights
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);

  // When not waiting for the player, play the pattern up to the current score
  if (!waiting) {
    count = 0;
    for (int i=0; i<=score; i++) {
      char color = pattern[i];
      if (color == 'B') showBlue();
      else if (color == 'G') showGreen();
      else if (color == 'Y') showYellow();
      else if (color == 'R') showRed();
      delay(250);
    }
    waiting = true;     // When the sequence is done playing, we are now waiting for the player
  }
  //For each button pressed, first light up the corresponding LED, play a tone, and then check if the button pressed is the correct one
  if (digitalRead(BTN_B)==LOW) {
     showBlue();
     check('B');
  }
  if (digitalRead(BTN_G)==LOW) {
     showGreen();
     check('G');
  }
  if (digitalRead(BTN_R)==LOW) {
     showRed();
     check('R');
  }
  if (digitalRead(BTN_Y)==LOW) {
     showYellow();
     check('Y');
  }

  delay(10);
}
void check(char x) {
  
  Serial.println(x);
  
  if (pattern[count] == x) {      // Is the letter at number count equal to the button pressed
    count++;                      // Increase the count
    if (count > score) {          // Did you just press the last button in the pattern?
      score++;                    // Increase the score
      count = 0;                  // Reset the count
      waiting = false;            // We are no longer waiting for the player

       //Display the score:
      display.clearDisplay();
      display.setCursor(1, 40);              // Start at top-left corner
      display.setTextSize(1);               // Set font size
      display.setTextColor(SSD1306_WHITE);  // Set color to white
      display.setFont(&FreeSansBold24pt7b);
      display.println(score, DEC);          // display the score as a decimal
      display.display();          
      delay(250);
    }
  } else {
    //  Game over
      Serial.println("your score:");
      Serial.println(score);

      tone(SPEAKER, 300);
      delay(400);
      tone(SPEAKER, 200);
      delay(300);
      tone(SPEAKER, 100);
      delay(400);
      noTone(SPEAKER);

      for (int i=0; i < score; i++) {
        tone(SPEAKER, (400 + 50*i));
        delay(200);
        noTone(SPEAKER);
        delay(200);
      }

      //Reset all variables
      score = 0;
      count = 0;
      pattern = "";
      setSequence();        //Generate a new pattern  
      waiting = false;
    }
  }
  delay(100);
}
void showRed() {
   digitalWrite(RED, HIGH);
   tone(SPEAKER,400);
   delay(250);
   noTone(SPEAKER);
   digitalWrite(RED, LOW); 
  
}
void showYellow() {
   digitalWrite(YELLOW, HIGH);
   tone(SPEAKER,500);
   delay(250);
   noTone(SPEAKER);
   digitalWrite(YELLOW, LOW); 
  
}
void showBlue() {
    digitalWrite(BLUE, HIGH);
    tone(SPEAKER,600);
    delay(250);
    noTone(SPEAKER);
    digitalWrite(BLUE, LOW); 
}
void showGreen() {
   digitalWrite(GREEN, HIGH);
   tone(SPEAKER,700);
   delay(250);
   noTone(SPEAKER);
   digitalWrite(GREEN, LOW); 
  
}

