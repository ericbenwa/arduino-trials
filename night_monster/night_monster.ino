#include <LiquidCrystal.h>
#include <Servo.h>

Servo servoRight; // Define our Servo
Servo servoLeft; 

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int echoPin = 7; 
int trigPin = 6;
int soundPin = 8;
int sensorPin = A5;
int sensorValue = 0;
int ledPin = 5;

void setup() { 
  Serial.begin (9600); 
  //lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(soundPin, OUTPUT);
  servoLeft.attach(12);
  servoRight.attach(13);
  servoLeft.write(30);
  servoRight.write(30);
  noTone(soundPin);
} 

void loop() { 
  int myDistance = readDistance();
  int myPitch = 0;

  Serial.print(myDistance);
  Serial.println(" cm");

  if (myDistance == 0) {
    myPitch = 0;
    noTone(soundPin);
  }
  else {
    myPitch = SetPitch(myPitch, abs(5000 - map(myDistance, 1, 25, 100, 5000)));
  }
  
  Serial.print(myPitch);
  Serial.println(" Hz");
  
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  /*
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(cm);
  lcd.print(" cm");
  lcd.setCursor(0, 1);
  lcd.print(thisPitch);
  lcd.print(" Hz");
  */
  if (sensorValue < 100) { 
    walk();
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, HIGH); 
  }
  delay(100); 
}

int readDistance() {
  int duration, cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  cm = duration / 29 / 2;
  return cm;
}

int SetPitch(int currentpitch, int newpitch) { 
  if (abs(newpitch - currentpitch) > 500) {
     noTone(soundPin);
     tone(soundPin, newpitch);
     return newpitch;
   }
   return currentpitch;
}

void walk() {
  servoLeft.write(60);
  servoRight.write(0);
  delay(250);
  servoLeft.write(0);
  servoRight.write(60);
  delay(250);
  servoLeft.write(30);
  servoRight.write(30);
  delay(150);
}
