const int magnetPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int magnetState= 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);     // initialize the LED pin as an output:   
  pinMode(magnetPin, INPUT);     
}

void loop(){
  // read the state of the magnet sensor value:
  magnetState = digitalRead(magnetPin);

  if (magnetState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin , HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin , LOW); 
  }
  delay(100);
}
