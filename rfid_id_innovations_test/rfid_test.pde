import processing.serial.*;

Serial myPort;
String tagID = "";

void setup() {
  size(150,150);
  println(Serial.list());
  
  String portnum = Serial.list()[8];
  myPort = new Serial(this, portnum, 9600);
  myPort.bufferUntil(0x03);
}

void draw() {
  background(#022e61);
  fill(#d9eadd);
  text(tagID, width/4, height/2);
}

void serialEvent(Serial myPort) {
  String inputString = myPort.readString();
  
  char firstChar = inputString.charAt(0);
  char lastChar = inputString.charAt(inputString.length() -1);
  
  if ((firstChar == 0x02) && (lastChar == 0x03)) {
    tagID = inputString.substring(1, 11);
  }
}
