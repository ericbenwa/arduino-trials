int sensorPin = A0; 
void setup(){
  Serial.begin(9600);}
 
void loop()                    
{
 int reading = analogRead(sensorPin);  
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 Serial.print(voltage); Serial.println(" volts");
 // now print out the temperature
 float temperatureC = (voltage ) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((volatge - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 // now convert to Fahrenheight
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 delay(1000);                                     //waiting a second
}
