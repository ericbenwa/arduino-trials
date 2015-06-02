#include <Trestle.h>
#include <SerialTrestle.h>

SerialTrestle bridge("Station1", "192.168.1.18", 4567, &Serial);

// Uses a PIR sensor to detect movement 

// more info here: makeprojects.com/Project/PIR-Sensor-ArduinoAlarm/72/1 

// email me, John Park, at jp@jpixl.net 

//based upon: 

// PIR sensor tester by Limor Fried of Adafruit 

// tone code by michael@thegrebs.com 

int ledPin = 13;                // choose the pin for the LED 

int inputPin = 2;               // choose the input pin (for PIR sensor) 

int pirState = LOW;             // we start, assuming no motion detected 

int val = 0;                    // variable for reading the pin status 

int pinSpeaker = 10;            // set up a speaker on a PWM pin (digital 9, 10, or 11) 

int pullUp = 0;                 // store number of pull ups

int currentTriggeredTime;

int result = bridge.registerStation("PullUpStation", "My Station Description", false);


void setup() { 

  pinMode(ledPin, OUTPUT);      // declare LED as output 

  pinMode(inputPin, INPUT);     // declare sensor as input 

  pinMode(pinSpeaker, OUTPUT); 

  Serial.begin(9600); 

} 

void loop(){ 

  val = digitalRead(inputPin);  // read input value 

  if (val == HIGH) {            // check if the input is HIGH 

    digitalWrite(ledPin, HIGH);  // turn LED ON 

    delay(10);
    
    
    

     

    if (pirState == LOW) { 

      // we have just turned on 

      Serial.println("Motion detected!"); 
      
      
      // We only want to print on the output change, not state 

      pirState = HIGH; 
      
      

    } 

  } else { 

    digitalWrite(ledPin, LOW); // turn LED OFF 

    delay(10);     

    if (pirState == HIGH){ 

      // we have just turned off 

      Serial.println("Motion ended!"); 

      // We only want to print on the output change, not state 
      
      pullUp++;               // add 1 pull up
      
      Serial.println(pullUp);

      pirState = LOW;     } 

  } 
  

}
