import processing.video.*;
import processing.net.*;
Capture myCam;
String fileName = "nerdcam.jpg";

String pictureScriptUrl = "/client/EJB/nerdcam/save2web.php";
String boundary = "----H4rkNrF";
Client thisClient;

void setup() {
  size(640, 480);
  
  println(Capture.list());
  
  myCam = new Capture(this, width, height, 30);
}

void draw() {
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

void keyReleased() {
  PImage img = get();
  img.save(fileName);
  postPicture();
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
