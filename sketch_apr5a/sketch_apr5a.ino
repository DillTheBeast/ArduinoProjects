Order[] = new Array[10];

int numInOrder

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  randomSeed(analogRead(0));

  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int randomNumber = random(1, 5);
  order.add(randomNumber);

  for(int i = 0; i < 10; i++) {
    numInOrder = Order[i];
    lightUp(numInOrder);
  }
}

void lightUp(int numInOrder) {
    if(numInOrder == 1) {
      //Red lights up

    }
    else if(numInOrder == 2) {
      //Yellow lights up

    }
    else if(numInOrder == 3) {
      //Green lights up

    }
    else {
      //Blue lights up

    }
}
