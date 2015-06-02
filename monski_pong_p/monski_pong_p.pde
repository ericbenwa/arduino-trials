import processing.serial.*;

Serial myPort;
String resultString;

void setup() {
  size(480,130);
  println(Serial.list());
  
  String portName = Serial.list()[4];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(#044f6f);
  fill(#ffffff);
  
  if(resultString != null) {
    text(resultString, 10, height/2);
  }
}

void serialEvent(Serial myPort) {
  String inputString = myPort.readStringUntil('\n');
  inputString = trim(inputString);
  resultString = "";
  
  int sensors[] = int(split(inputString, ','));
  
  for (int sensorNum = 0; sensorNum < sensors.length; sensorNum++) {
    resultString += "Sensor " + sensorNum + ": ";
    resultString += sensors[sensorNum] + "\t";
  }
  
  println(resultString);
}
  
  
  
