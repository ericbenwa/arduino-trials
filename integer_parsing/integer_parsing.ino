// this will allow you to type into the monitor to input
// a value to dim the light, change its intensity

void setup() { 
  Serial.begin(9600);  		//Initialize serial and wait for port to open
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

int number = 0;

void loop(){
 if(Serial.available() != 0){
   number = Serial.parseInt();
 } 
 analogWrite(11, number);
}
