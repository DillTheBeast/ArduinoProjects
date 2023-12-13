
void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(9) == LOW) {
    /*
    for(int i = 0; i < 255; i++) {
      analogWrite(10, i);
    }
    */
    digitalWrite(11, HIGH);
  }

}
