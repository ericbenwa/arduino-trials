// Sensor Counter

// more info here: makeprojects.com/Project/PIR-Sensor-ArduinoAlarm/72/1
// email me, John Park, at jp@jpixl.net
// based upon:
// PIR sensor tester by Limor Fried of Adafruit
// tone code by michael@thegrebs.com

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pullUp;                   // sets number times sensor went on
int currentTriggeredTime;       // 
int sensorGoal = 10;

void setup() {

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps

}


void loop(){

  val = digitalRead(inputPin);  // read input value


  if (val == HIGH) {            // check if the input is HIGH

    digitalWrite(ledPin, HIGH); // turn LED ON
    delay(10);


    if (pirState == LOW) {
      // Serial.println("Motion detected!");

      pirState = HIGH;
    }

  } else {

    digitalWrite(ledPin, LOW);   // turn LED OFF
    delay(10);

    if (pirState == HIGH){
      // Serial.println("Motion ended!");

      pullUp++;                // add 1 to sensor counter
      Serial.write(pullUp);
      Serial.println(pullUp);
      pirState = LOW;
    }

  }
  
  if (pullUp == sensorGoal) {
    Serial.println("GOALLLL!!!!!");
  }
  
}
