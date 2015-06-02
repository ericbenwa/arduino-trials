int configPin = 13;                 //Set the sonar Calibration Pin
void setup() {                    //begin of program
Serial.begin(9600);             //serial baud rate 9600
pinMode(configPin,OUTPUT);       //make Calibration pin output
}
void loop(){                     //looping of program
digitalWrite(configPin,HIGH);    //raise the reset pin high
delay(50);                      //start of calibration ring
float sensorvalue = analogRead(0); //get analog sensor value from pin 0
float inchvalue = (254.0/1024.0) *2.0* sensorvalue; //convert to inches
Serial.print("Sensed a-d value:"); //print a-d text
Serial.println(sensorvalue);       //print a-d value
Serial.print("Inch value=");      //print inch text
Serial.println(inchvalue);        //print inch value
delay(50);                      //optional delay 1 second
digitalWrite(configPin,LOW);      //turn off Calibration ring and sensor
delay(50);                      //delay 1 second
}
