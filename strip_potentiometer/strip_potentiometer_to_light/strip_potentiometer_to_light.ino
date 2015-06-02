int led = 11;
int ledvalue;

void setup(){
  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  analogWrite(led, 255);
  
}

void loop(){
  Serial.println(analogRead(A0));
  delay(50);
  
  ledvalue = analogRead(A0);
  Serial.println(ledvalue);
  ledvalue = map(ledvalue, 0, 1023, 0, 255);
  analogWrite(led, ledvalue);
  
}
