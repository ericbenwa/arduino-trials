import processing.serial.*;
Serial myPort;
String binaryString = "";
String asciiString = "";

void setup() {
  size(500,200);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[8], 19200);
}

void draw() {
  background(#7b9b9d);
  fill(#59462e);
  text(binaryString, 10, height/3);
  text(asciiString, 10, 2*height/3);
}

void keyReleased() {
  int command = 0x81;
  int dataLength = 1;
  if (key == 's') {
    command = 0x83;
  }
  
  myPort.write(0xFF);
  myPort.write(0x00);
  myPort.write(dataLength);
  myPort.write(command);
  myPort.write(command + dataLength);
  binaryString = "";
  asciiString = "";
}

void serialEvent(Serial myPort) {
  char thisChar = (char)myPort.read();
  binaryString += hex(thisChar, 2) + " ";
  asciiString += thisChar;
}
