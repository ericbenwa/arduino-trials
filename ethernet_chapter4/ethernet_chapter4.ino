#include <SPI.h>
#include <Ethernet.h>

Server server(80);

byte mac[] = { };
IPAddress gateway( );
IPAddress subnet( );
IPAddress ip ( );

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet, ip);
  server.begin();
  Serial.begin(9600);
}

void loop() {
  Client client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char thisChar = client.read();
        Serial.write(thisChar);
      }
    }
    client.stop();
  }
}
