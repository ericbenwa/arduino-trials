const int greenPin = 6;
const int bluePin = 7;
const int redPin = 5;

int currentPin = 0;
int brightness = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop(){
 if (Serial.available() > 0) {
  int inByte = Serial.read();
 
  if (inByte == 'r') {
   currentPin = redPin;
  }
  if (inByte == 'g') {
   currentPin == greenPin;
  }
  if (inByte == 'b') {
   currentPin = bluePin;
  }
  if (inByte >= '0' && inByte <= '9') {
   brightness = map(inByte, '0', '9', 0, 255);
  analogWrite(currentPin, brightness);
  }
 } 
}
