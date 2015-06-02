/*
Pull Up Device
by Eric Benoit
*/


int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int pullUpsTotal;               // records the total of pull ups for the day
int goal = 3;                   // sets a personal goal for daily pull ups (eventually will be user defined)
int goalStatus = 0;             // 0 = not achieved, 1 = achieve daily goal
int goalLED;                    // visual feedback of todays progress towards goal (future)

int currentDate = 98;           // set to 98 and 99 for testing purposes until I can actively scrape date
int todaysDate = 99;

long timeSinceLastPullUp;       // using a timer between pull ups to identify inactivity
int timerStatus = 0;            // 0 = timer off, 1 = timer on


void setup() {

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);           // opens serial port, sets data rate to 9600 bps

}


void loop(){
 // this loop is kind of messy... based off tutorial...
 
  val = digitalRead(inputPin);             // read input value
  
  // Serial.println(timeSinceLastPullUp);
  // timeSinceLastPullUp = millis();
  
  if (val == HIGH) {                       // check if the input is HIGH

    digitalWrite(ledPin, HIGH);            // turn LED ON
    delay(10);

    if (pirState == LOW) {
      // Serial.println("Motion detected!");
      pirState = HIGH;
    }

  } else {

    digitalWrite(ledPin, LOW);             // turn LED OFF
    delay(10);

    if (pirState == HIGH){                 // This detects when motion has ended
      pullUpSuccess();
      pirState = LOW;
    }

  }
  
  timer();
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
  timeSinceLastPullUp = 0;                 // resetting the timer to 0 to let the device know the person is still active
  timerStatus = 1;                         // starting the timer 
  Serial.print("Timer reset to ");
  Serial.println(timeSinceLastPullUp);
  Serial.print(pullUpsTotal);
  Serial.println(" = pull up total");

  if (pullUpsTotal == goal){
    // audio feedback for reaching daily goal (maybe some Mr T motivation!?)
    goalStatus = 1;                        // this says the goal has been reached for the day
    Serial.print("Goal has been achieved, ");
    Serial.println(goalStatus);
  } else {
    // audio feedback for a pull up
  }
  
}


void timer(){
  
  if (timerStatus == 1){
    Serial.print(timeSinceLastPullUp);
    Serial.println(" time passed");
    timeSinceLastPullUp = millis();        // not set up for my need, this counter start as soon as the app starts, regardless if the time status is 1
  }

}


void sendData(){

  if (timeSinceLastPullUp > 30000){        // after 30 seconds from last pull up lets upload the data
    // connect to wifi (plan for wifi not working and storing data for N days)
    timeSinceLastPullUp = 0;               // (not working) resetting the timer to 0 so the device doesn't keep uploading data
    timerStatus = 0;                       // stopping the timer
    // send pullUpsTotal to web
    // send goal status to web
    // disconnect from wifi
    // go into standy mode
    Serial.println("----------");
    Serial.println("Data sent!");
    Serial.print(pullUpsTotal);
    Serial.println(" pull ups for daily total");
    Serial.print("Goal is, ");
    Serial.println(goalStatus);
    Serial.println("----------");
  }

}


/*
Credits
John Park - makeprojects.com/Project/PIR-Sensor-ArduinoAlarm/72/1
*/
