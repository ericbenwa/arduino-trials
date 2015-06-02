int ledPin = 13;
volatile int state = LOW;

void setup(){
  pinMode(ledPin , OUTPUT);
  attachInterrupt(0, blink, CHANGE);
}

void loop(){
  digitalWrite(ledPin , state);
}

void blink(){
  state = !state;
}
