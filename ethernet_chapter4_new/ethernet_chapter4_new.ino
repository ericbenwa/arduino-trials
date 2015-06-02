#include <SPI.h>
#include <Ethernet.h>

EthernetServer server(80);

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);
IPAddress ip(10,0,1,20);

int lineLength;

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char thisChar = client.read();
        if (thisChar == '\n' && lineLength < 1) {
          makeResponse(client);
          break;
        }
        if (thisChar == '\n' || thisChar == '\r') {
          lineLength = 0;
        } else {
          lineLength++;
        }
      }
    }
    delay(1);
    client.stop();
  }
}

void makeResponse(EthernetClient thisClient) {
  thisClient.print("HTTP/1.1 200 OK\n");
  thisClient.print("Content-Type: text/html\n\n");
  thisClient.print("<html><head><meta http-equiv=\"refresh\" content=\"3\">");
  thisClient.print("<title>hello from arduino</title></head>");
  thisClient.print("<body bgcolor=#");
  int red = analogRead(A0)/4;
  int green = analogRead(A1)/4;
  int blue = analogRead(A2)/4;
  thisClient.print(red, HEX);
  thisClient.print(green, HEX);
  thisClient.print(blue, HEX);
  thisClient.print(">");
  thisClient.print("the color of the light on the arduino is #");
  thisClient.print(red, HEX);
  thisClient.print(green, HEX);
  thisClient.print(blue, HEX);
  
  thisClient.println("</body></html>\n");
  
  for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
    thisClient.print("analog input ");
    thisClient.print(analogChannel);
    thisClient.print(" is ");
    thisClient.print(analogRead(analogChannel));
    thisClient.print("<br />\n");
  }
}
