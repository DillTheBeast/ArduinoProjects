int buttonPin = 10;
int buttonState = 0;

void setup() {
  // initialize the button pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
   buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed (5V, HIGH):
  if (buttonState == HIGH) {
    // if it is, print "hi":
    Serial.println("hi");
    delay(1000); // Add a delay to avoid excessive prints when the button is held down
  }                     // Wait for 1 second
}
