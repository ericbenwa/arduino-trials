int led = 13;
//int led = 11;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  
  digitalWrite(led, HIGH);
  delay(1);
  digitalWrite(led, LOW);
  delay(10);
  Serial.print(led);
  
  /*
  analogWrite(led, 255);
  delay(100);
  analogWrite(led, 128);
  delay(100);
  */
}
