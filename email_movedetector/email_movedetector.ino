int pirPin = 7;
int pullup = 0;
int minSecsBetweenEmails = 60; // 1 min
 
long lastSend = -minSecsBetweenEmails * 1000l;
 
void setup()
{
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  long now = millis();
  if (digitalRead(pirPin) == HIGH)
  {
    if (now > (lastSend + minSecsBetweenEmails * 1000l))
    {
      Serial.println("MOVEMENT");
      lastSend = now;
      pullup = 5;
      Serial.println(pullup);
    }
    else
    {
      Serial.println("Too soon");
    }
  }
  delay(500);
}
