
import processing.serial.*;
import processing.video.*;
import processing.net.*;

Serial myPort;
float sensorValue = 0;
float prevSensorValue = 0;
int threshold = 150;

int currentTime = 0;
int lastMailTime = 0;
int mailInterval = 60;
String mailUrl = "http://www.ebenoit.com/client/EJB/nerdcam/catscript.php";
int lastPictureTime = 0;
int pictureInterval = 10;

Capture myCam;
String fileName = "nerdcam.jpg";

String pictureScriptUrl = "/client/EJB/nerdcam/save2web.php";
String boundary = "----H4rkNrF";
Client thisClient;

float xPos = 0;
float lastXPos = 0;

void setup() {
  size(400,300);
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[6], 9600);
  myPort.bufferUntil('\n');
  
  background(#543174);
  smooth();
  
  println(Capture.list());
  
  myCam = new Capture(this, width, height, 30);
}

void draw() {
  currentTime = hour() * 3600 + minute() * 60 + second();
  
  if (myCam.available()) {
    myCam.read();
    set(0, 0, myCam);
    
    String timeStamp = nf(hour(), 2) + ":" + nf(minute(), 2) + ":" + nf(second(), 2) + " " + nf(day(), 2) + "-" + nf(month(), 2) + "-" + nf(year(), 4);
    
    fill(15);
    text(timeStamp, 11, height - 19);
    fill(255);
    text(timeStamp, 10, height - 20);
  }
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    inString = trim(inString);
    sensorValue = float(inString);
    sensorValue = map(sensorValue, 0, 500, 0, height);
   // println(sensorValue);
    
    if (sensorValue > threshold) {
      if (currentTime - lastPictureTime > pictureInterval) {
        PImage thisFrame = get();
        thisFrame.save(fileName);
        postPicture();
        lastPictureTime = currentTime;
      }
      
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

void postPicture() {
  byte[] thisFile = loadBytes(fileName);
  
  thisClient = new Client(this, "www.ebenoit.com", 80);
  thisClient.write("POST " + pictureScriptUrl + " HTTP/1.1\n");
  thisClient.write("Host: www.ebenoit.com\n");
  thisClient.write("Content-Type: multipart/form-data; boundary=");
  thisClient.write(boundary + "\n");
  
  String requestHead = "\n--" + boundary + "\n";
  requestHead += "Content-Disposition: form-data; name=\"file\"; ";
  requestHead += "filename=\"" + fileName + "\"\n";
  requestHead += "Content-Type: image/jpeg\n\n";
  
  String tail = "\n--" + boundary + "--\n\n";
  
  int contentLength = requestHead.length() + thisFile.length + tail.length();
  thisClient.write("Content-length: " + contentLength + "\n\n");
  
  thisClient.write(requestHead);
  thisClient.write(thisFile);
  thisClient.write(tail);
  
  thisClient.stop();
}
