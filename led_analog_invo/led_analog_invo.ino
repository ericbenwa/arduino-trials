int led = 10;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, 20);
  //delay(1000);
  //analogWrite(led, 0);
  //delay(500);
}
