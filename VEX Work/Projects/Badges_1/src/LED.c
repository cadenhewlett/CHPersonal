#include "main.h"
#include "LED.h"

void LEDState(){
  while(true){
    if(!isEnabled()){
      digitalWrite(LED, HIGH); //writes high to LED if robot is disabled
    }else{
      digitalWrite(LED, LOW); //otherwise the LED is off
    }
  }
}
