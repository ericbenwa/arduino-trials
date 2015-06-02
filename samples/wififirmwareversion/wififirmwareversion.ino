 #include <SPI.h>
 #include <WiFi.h>

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  Serial.println(WiFi.firmwareVersion());
}

void loop () {}
