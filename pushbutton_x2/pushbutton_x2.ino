#include <OneButton.h>

OneButton myButton(13,true);

void setup(){
  Serial.begin(9600);
  pinMode(13, INPUT);
  myButton.attachClick(myFunction);
  myButton.attachPress(myOtherFunction);
}

void loop(){
  myButton.tick();
}

void myFunction(){
  Serial.println("single");
}

void myOtherFunction(){
  Serial.println("double");
}
