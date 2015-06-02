#include <SPI.h>
#include <WiFi.h>

/*
Pull Up Device
by Eric Benoit
*/

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int pullups_total_arduino;      // total number of pull ups for the day
String pullup_string = "pullups_total=";
String pullups_total;
long timeBetween;               // using a timer between pull ups to identify inactivity
long timestampOfLastPullUp;     // when my last pullup started
long elapsedTimeSinceLastPullUp;// time between pull ups, used to determine active status
int activePerson = 0;

// Wifi Setup
char ssid[] = "flux capacitor"; //  your network SSID (name) 
char password[] = "applepie";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient client;

// Server address
char server[] = "www.ebenoit.com";


void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps
}


void loop(){
 // this loop is kind of messy, don't judge me... based off a tutorial...
 
  val = digitalRead(inputPin);             // read input value
  
  if (val == HIGH) {                       // check if the input is HIGH

    digitalWrite(ledPin, HIGH);            // turn LED ON
    delay(10);

    if (pirState == LOW) {
      // We were low before, but are high now
      // Serial.println("Motion detected!");
      pirState = HIGH;
    }
    else{
      // We were high before and high now
      // So there's no change.
    }

  } else {
    // Our value is low.
    digitalWrite(ledPin, LOW);             // turn LED OFF
    delay(10);

    if (pirState == HIGH){                 // This detects when motion has ended
      pullUp();
      pirState = LOW;
    }

  }
  
  sendData();

}


void pullUp(){                             // actions performed for each pull up
  pullups_total_arduino++;                 // adding 1 to todays pull up total
  long currentTime = millis();
  activePerson = 1;
  timeBetween = currentTime - timestampOfLastPullUp;     
  timestampOfLastPullUp = currentTime;  
  Serial.print("Time since last pullup ");
  Serial.println(timeBetween);
  Serial.print(pullups_total_arduino);
  Serial.println(" = pull up total");
}


void sendData(){                          // actions performed when we want to upload data to the web
  // If I am currently doing pullups, then let's see if I've finished
  if (activePerson == 1) {
    long currentTime = millis();
    elapsedTimeSinceLastPullUp = currentTime - timestampOfLastPullUp;
 
    if (elapsedTimeSinceLastPullUp > 30000){              // after 30 seconds from last pull up lets upload the data
      connectWifi();
      Serial.println("Attempting to send data");
      postData();
      Serial.println("----------");
      Serial.println("Data sent!");
      Serial.print(pullups_total_arduino);
      Serial.println(" pullups sent.");
      Serial.print("String pullups_total = ");
      Serial.println(pullups_total);
      client.stop();
      Serial.println("Disconnected from Wifi");
      Serial.println("----------");
      pullups_total_arduino = 0;
      timeBetween = 0;                    // (not working) resetting the timer to 0 so the device doesn't keep uploading data
      activePerson = 0;
    }
  }
}


void postData() {
  pullups_total = pullup_string + pullups_total_arduino;

  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    client.println("POST /client/EJB/pullups/insert_mysql.php HTTP/1.1");
    client.println("Host: www.ebenoit.com");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(pullups_total.length());
    client.println();
    client.println(pullups_total);
  } 
  else {
    Serial.println("Connection failed");
    Serial.println("Disconnecting.");
    client.stop();
  }
}


void connectWifi() {
  while (status != WL_CONNECTED) {
    Serial.println("----------");
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    delay(10000);
  }
  printWifiStatus();
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/*
Credits
Dhaval Karwa
Ben Salinas
John Park - makeprojects.com/Project/PIR-Sensor-ArduinoAlarm/72/1
Tom Igoe - arduino.cc/en/Tutorial/WiFiWebClientRepeating
*/
