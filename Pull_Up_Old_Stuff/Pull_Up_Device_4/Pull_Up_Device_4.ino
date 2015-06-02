#include <Trestle.h>
#include <SerialTrestle.h>

/*
Pull Up Device
by Eric Benoit
*/

SerialTrestle bridge("PullUps", "trestle.herokuapp.com", 80, &Serial);

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int pullUpsTotal;               // total number of pull ups for the day
int goal = 5;                   // sets a personal goal for daily pull ups (eventually will be user defined)
int goalStatus = 0;             // 0 = not achieved, 1 = achieve daily goal
int goalLED;                    // visual feedback of todays progress towards goal (future)

int currentDate = 98;           // set to 98 and 99 for testing purposes until I can active only scrape date
int todaysDate = 99;

long timeBetween;               // using a timer between pull ups to identify inactivity
long timestampOfLastPullUp;     // when my last pullup started
long elapsedTimeSinceLastPullUp;// time between pull ups, used to determine active status
int activePerson = 0;


void setup() {

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps
  
  // This will create a web page for this station.
  int response = bridge.registerStation("My fuggin Station Name", "all my pull up poops", false);
   
  // Add our two sensors by passing the station identifier, an identifier for the sensor, the name, description, and units.
  response = bridge.addSensor("MyFirstSensor", "Pull Ups", "total number...", "Milliseconds");
  bridge.addState("GoalReached", "A/C On", "Whether the Air Conditioner is On");  

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
      pullUpSuccess();
      pirState = LOW;
    }

  }
  
  sendData();

}


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


void pullUp(){                             // actions performed for each pull up

  pullUpsTotal++;                          // adding 1 to todays pull up total
  long currentTime = millis();
  activePerson = 1;
  timeBetween = currentTime - timestampOfLastPullUp;     
  timestampOfLastPullUp = currentTime;  
  Serial.print("Time since last pullup ");
  Serial.println(timeBetween);
  Serial.print(pullUpsTotal);
  Serial.println(" = pull up total");

  if (pullUpsTotal == goal){
    // audio feedback for reaching daily goal (maybe some Mr T motivation!?)
    goalStatus = 1;                        // this says the goal has been reached for the day
    bridge.setStateValue("GoalReached", "Goal Reached"); 
    Serial.print("Goal has been achieved, ");
    Serial.println(goalStatus);
  } else {
    // audio feedback for a pull up
  }
  
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
      // send pullUpsTotal to web
      // send goal status to web
      // disconnect from wifi
      // go into standy mode
      Serial.println("----------");
      Serial.println("Data sent!");
      Serial.print(pullUpsTotal);
      Serial.println(" pull ups for todays daily total");
      Serial.print("Goal is, ");
      Serial.println(goalStatus);
      Serial.println("----------");
      bridge.sendSensorData("MyFirstSensor", pullUpsTotal, 1); 
    }
  }

}


/*
Credits
Ben Salinas
John Park - makeprojects.com/Project/PIR-Sensor-ArduinoAlarm/72/1
*/
