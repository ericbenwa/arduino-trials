#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 6, 7);
int echoPin = 2; 
int trigPin = 3; 

void setup() { 
  Serial.begin (9600); 
  lcd.begin(16, 2);
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

  Serial.print(cm); 
  Serial.println(" cm");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(cm);
  lcd.print(" cm");
  delay(100); 
}
