int motor = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(motor, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(motor, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
