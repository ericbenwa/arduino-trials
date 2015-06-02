#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,6);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(8,9);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil
float value = 1.0;
void setup()                    
{
//   cs_4_2.set_CS_AutocaL_Millis(20000);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}


void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_4_5.capacitiveSensor(30);
    long total3 =  cs_4_8.capacitiveSensor(30);

    if(total3 > 50){
      
      Serial.print(millis() - start);        // check on performance in milliseconds
      Serial.print("\t");                    // tab character for debug window spacing
  
      Serial.print(total1);                  // print sensor output 1
      Serial.print("\t");
      Serial.print(total2);                  // print sensor output 2
      Serial.print("\t");
  //    Serial.print(total3);                  // print sensor output 2
  //    Serial.print("\t");
  
      if(total1 != 0 || total2 != 0) {
        value = 0.5*value + 0.5*((float)total1/((float)total2 + (float)total1));
        Serial.print(100*value);
        
      } else {
  //      Serial.println();
      }
    }
    int valToWrite = map((100*value), 17,100, 1,254);
        analogWrite(11, min(max(0,valToWrite),255));
        Serial.print("\t");
        Serial.println( min(max(0,valToWrite),255));

    delay(50);                             // arbitrary delay to limit data to serial port 
}
