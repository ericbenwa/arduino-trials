void setup() { 
  Serial.begin(9600);  		//Initialize serial and wait for port to open
  pinMode(13, OUTPUT);
}

char incoming;
void loop() {
 if(Serial.available() != 0) {
  incoming = Serial.read();
  if(incoming == 't') {
   digitalWrite(13,true);
  }
 if(incoming == 'f'){
  digitalWrite(13,false);
  Serial.print("fuck");
 } 
}
}
