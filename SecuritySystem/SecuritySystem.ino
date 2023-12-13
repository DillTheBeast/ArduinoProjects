#define Trig 2
#define Echo 3

bool bypass = false;
int bypassTime = 20;
int lastTime;
int nowTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Setting up the sensor
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(12, OUTPUT);
  pinMode(11, INPUT_PULLUP);

}

void loop() {
  nowTime = millis();
  int timeDiff = nowTime - lastTime;
  // put your main code here, to run repeatedly:
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(Trig, LOW);

  float t = pulseIn(Echo, HIGH);
  float distance = t*0.017015;


  if(digitalRead(11) == LOW && bypass == false) {
    Serial.println("Test1");
    bypass = true; 
    bypassTime = 20;
  }

  if(bypass == true) {
    if(timeDiff > 980) {
      timeDiff = 0;
      lastTime = nowTime;
      bypassTime -= 1;
    }
  }
  
  if(bypassTime == 0 && bypass == true) {
    bypass = false;
  }

  if(distance <= 91 && bypass == false) {
    Serial.println("Hello");
    digitalWrite(12, HIGH);
    //delay(2000);
  }
  else {
    digitalWrite(12, LOW);
  }
}
