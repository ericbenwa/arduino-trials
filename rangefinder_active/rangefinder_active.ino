int echoPin = 2; 
int trigPin = 3;
int active = 0;
int pullups = 0;

void setup() { 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
} 

void loop() { 
  int duration, cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH); 
  cm = duration / 29 / 2;
  Serial.println(cm);
  
  /*
  if (cm < 20 && active == 0) {
    pullups++;
    active = 1;
    Serial.println(pullups);
    Serial.println(cm);
  } 
  if (cm > 20 || cm == 0) {
    active = 0;
    Serial.println("nothing to see");
  }
  */
}
