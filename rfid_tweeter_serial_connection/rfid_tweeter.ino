#include <SoftwareSerial.h>

SoftwareSerial rfid(7, 8);

void setup() {
  rfid.begin(19200);
  Serial.begin(19200);
}

void loop() {
  if (Serial.available()) {
    rfid.write(Serial.read());
  }
  
  if (rfid.available()) {
    Serial.write(rfid.read());
  }
}
