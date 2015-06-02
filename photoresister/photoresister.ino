int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 6;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin, OUTPUT);    // declare the ledPin as an OUTPUT
   Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);      // read the value from the sensor:
   Serial.println(sensorValue);
  digitalWrite(ledPin, HIGH);    // turn the ledPin on
  delay(sensorValue);            // stop the program for <sensorValue> milliseconds:
  digitalWrite(ledPin, LOW);     // turn the ledPin off:        
  delay(sensorValue);              // stop the program for for <sensorValue> milliseconds:
}
