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

int pullups_total_arduino;               // total number of pull ups for the day
//int goal = 10;                   // sets a personal goal for daily pull ups (eventually will be user defined)
//int goalStatus = 0;             // 0 = not achieved, 1 = achieve daily goal
int goalLED;                    // visual feedback of todays progress towards goal (future)

long timeBetween;               // using a timer between pull ups to identify inactivity
long timestampOfLastPullUp;     // when my last pullup started
long elapsedTimeSinceLastPullUp;// time between pull ups, used to determine active status
int activePerson = 0;

// Wifi Setup
char ssid[] = "flux capacitor";      //  your network SSID (name) 
char pass[] = "applepie";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// Server address:
char server[] = "www.ebenoit.com";
String pullupstring = "pullups_total=";
String pullups_total;


unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
boolean lastConnected = false;                  // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds


void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
    // you're connected now, so print out the status:
  printWifiStatus();
}


void loop(){
 // this loop is kind of messy, don't judge me... based off a tutorial...
 
  val = digitalRead(inputPin);             // read input value
  
  // Serial.println(timeBetween);
  // timeBetween = millis();
  
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
      //pullUpSuccess();
      pullUp();
      pirState = LOW;
    }

  }
  
  sendData();

  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  /*if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    httpRequest();
  }*/
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();

}

/*
void pullUpSuccess(){

  if (currentDate == todaysDate){          // if the date is the same lets keep adding to todays total pull ups
    Serial.println("Same day");
    pullUp();
  } else {                                 // since it's a new day we'll need to reset the pullUpsTotal and goal back to 0
    Serial.println("New day");
    todaysDate = currentDate;
    pullUpsTotal = 0;                      // resetting the pullUpsTotal for the new day
    Serial.print("Pull ups reset to ");
    Serial.println(pullUpsTotal);
    goalStatus = 0;                        // resetting the goal success for the new day
    Serial.print("Goal reset to not yet achieved, ");
    Serial.println(goalStatus);
    pullUp();
  }

}
*/


void pullUp(){                             // actions performed for each pull up

  pullups_total_arduino++;                          // adding 1 to todays pull up total
  long currentTime = millis();
  activePerson = 1;
  timeBetween = currentTime - timestampOfLastPullUp;     
  timestampOfLastPullUp = currentTime;  
  Serial.print("Time since last pullup ");
  Serial.println(timeBetween);
  Serial.print(pullups_total_arduino);
  Serial.println(" = pull up total");

  /*if (pullUpsTotal == goal){
    // audio feedback for reaching daily goal (maybe some Mr T motivation!?)
    goalStatus = 1;                        // this says the goal has been reached for the day
    Serial.print("Goal has been achieved, ");
    Serial.println(goalStatus);
  } else {
    // audio feedback for a pull up
  }
  */
  
}


void sendData(){                          // actions performed when we want to upload data to the web
  // If I am currently doing pullups, then let's see if I've finished
  if (activePerson == 1) {
    long currentTime = millis();
    elapsedTimeSinceLastPullUp = currentTime - timestampOfLastPullUp;
 
    if (elapsedTimeSinceLastPullUp > 30000){              // after 30 seconds from last pull up lets upload the data
      // connect to wifi (plan for wifi not working and storing data on device for N days)
      timeBetween = 0;                    // (not working) resetting the timer to 0 so the device doesn't keep uploading data
      activePerson = 0;
      pullups_total = pullupstring + pullups_total_arduino;
      // send pullUpsTotal to web
      // send goal status to web
      // disconnect from wifi
      // go into standy mode
      httpRequest();
      Serial.println("----------");
      Serial.println("Data sent!");
      Serial.print(pullups_total_arduino);
      Serial.println("String pullups_total");
      Serial.print(pullups_total);
      Serial.println(" pull ups for todays daily total");
      pullups_total_arduino = 0;
      Serial.print("Goal is, ");
      //Serial.println(goalStatus);
      //Serial.println("----------");
    }
  }

}


// this method makes a HTTP connection to the server:
void httpRequest() {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("POST /client/EJB/pullups/insert_mysql.php HTTP/1.1");
    client.println("Host: www.ebenoit.com");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(pullups_total.length());
    client.println();
    client.println(pullups_total);

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
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
*/
