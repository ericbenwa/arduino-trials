int led13 = 13;
int led12 = 12;
int led11 = 11;
int led10 = 10;

void setup() {
  Serial.begin(9600);
  pinMode(led13, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop() {
  digitalWrite(led13, HIGH);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, HIGH);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, LOW);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, HIGH);
  delay(100);
  digitalWrite(led13, LOW);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  delay(100);
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, HIGH);
  delay(250);
  /*
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, HIGH);
  delay(1000);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  delay(1000);
  digitalWrite(led13, LOW);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, LOW);
  delay(1000);
  */
  //delay(1);
  //digitalWrite(led3, LOW);
  //delay(25);
}
