

int lastVal = 1;
int presses = 0;

void setup(){
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop(){
  
  int currentVal = digitalRead(13);
  
  if(lastVal == 1 && currentVal == 0){
   presses++; 
   Serial.println(presses);
  }
  lastVal = currentVal;
}
