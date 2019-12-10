#include "main.h"
#include "angler.h"

void Angler_Task_fn(void * para){
  
  int err = 0;
  int err_last = 0;
  int currentValue;
  int targetValue;
  bool buttonStop = false;
  int motorPower;
  int cap;
  int derr;

  while(true){

    currentValue = abs(TrayPot.get_value());

    if(competition::is_autonomous()){
      targetValue = anglerAutoTarget; //autonomous control is a variable changed in autonomous.cpp
    }
    else{
      if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
        targetValue = 0;
        buttonStop = true;
      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
        targetValue = 870;
        buttonStop = false;
      }
    }

    if((targetValue == 870) && (currentValue > 350)){ //if we're going to highest preset and we're past appx. halfway
      cap = 50; //slow down so we don't knock down the tower
    }
    else{
      cap = 127; //otherwise move normally
    }

    err = targetValue - currentValue; //error is delta of target and current positions
    err_last = err; //store last error
    derr = err - err_last; //difference of errors over iterations
    motorPower = (0.7 * err) + (1.35 * derr); //PD constants plus our variables
    motorPower = motorPower > cap ?  cap : motorPower < -127 ? -127 : motorPower; //caps output at +cap, -127

    if(buttonStop && (button.get_value() == HIGH)){  //if our active stop variable is true AND the digital button is pressed
      TrayMotor.move(0); //stop movement, to prevent the motor from overheating
    }
    else{
      TrayMotor.move(-motorPower); //move the lift equal to motorPower, meaning standard PD movement
    }
  }
}
