bool lightOn = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    char c = Serial.read();
    if(c) {
      if(c == 'A') {
        lightOn = true;
      }
      else if(c == 'Z') {
        lightOn = false;
      }
      c = NULL;
    }
  }
  if(lightOn) {
    digitalWrite(11, HIGH);
    Serial.println("on");
  }
  else {
    digitalWrite(11, LOW);
    Serial.println("off");
  }

  delay(1000);
}
