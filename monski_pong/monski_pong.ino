
const int leftsensor = A0;
const int rightsensor = A1;
const int resetbutton = 2;
const int servebutton = 3;

int leftvalue = 0;
int rightvalue = 0;
int reset = 0;
int serve = 0;

void setup() {
  pinMode(resetbutton, INPUT);
  pinMode(servebutton, INPUT);
}

void loop() {
  leftvalue = analogRead(leftsensor);
  rightvalue = analogRead(rightsensor);
  
  reset = digitalRead(resetbutton);
  serve = digitalRead(servebutton);
  
  Serial.print(leftvalue);
  Serial.print(".");
  Serial.print(rightvalue);
  Serial.print(".");
  Serial.print(reset);
  Serial.print(".");
  Serial.println(serve);
}
