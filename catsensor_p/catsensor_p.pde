
import processing.serial.*;

float prevSensorValue = 0;
float lastXPos = 0;

int threshold = 150;

int currentTime = 0;
int lastMailTime = 0;
int mailInterval = 60;
String mailUrl = "http://www.ebenoit.com/client/EJB/nerdcam/catscript.php";

Serial myPort;
float sensorValue = 0;
float xPos = 0;

void setup() {
  size(400,300);
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[6], 9600);
  myPort.bufferUntil('\n');
  
  background(#543174);
  smooth();
}

void draw() {
  currentTime = hour() * 3600 + minute() * 60 + second();
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    inString = trim(inString);
    sensorValue = float(inString);
    sensorValue = map(sensorValue, 0, 500, 0, height);
   // println(sensorValue);
    
    sensorValue = map(sensorValue, 0, 500, 0, height);
    drawGraph(prevSensorValue, sensorValue);
    
    if (sensorValue > threshold) {
      if (prevSensorValue <= threshold) {
        println("cat on the mat");
        sendMail();
      }
    } else {
      if (prevSensorValue > threshold) {
        println("cat NOT on mat");
      }
    }
    prevSensorValue = sensorValue;
  }
}

void drawGraph(float prevValue, float currentValue) {
  float yPos = height - currentValue;
  float lastYPos = height - prevValue;
  
  stroke(#c7afde);
  line(lastXPos, lastYPos, xPos, yPos);
  
  if (xPos >= width) {
    xPos = 0;
    lastXPos = 0;
    background(#543174);
  } else {
    xPos++;
    lastXPos = xPos;
  }
}

void sendMail() {
  int timeDifference = currentTime - lastMailTime;
  
  if (timeDifference > mailInterval) {
    String[] mailScript = loadStrings(mailUrl);
    println("results from mail script");
    println(mailScript);
    
    lastMailTime = currentTime;
  }
}
