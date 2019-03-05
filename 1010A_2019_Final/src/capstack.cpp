#include "main.h"
#include "angler.h"
#include "capstack.h"
/*
This is a PID Controller for the Cap Stacking Arm that is running as a permanent task.
The target of this controller is changed by changing the global variable 'caoTarget' in any location.
This task is started in initialize.cpp and is  referenced in opcontrol.cpp and autonomous..
There is another Global Variable called "cap max" which will control the max and min output, and is
also changed in autonomous.cpp and opcontrol.cpp, defined in initialize.cpp
NOTE: See PID Controller: https://en.wikipedia.org/wiki/PID_controller
*/
void CAPSTACK_Task_fn(void*parameter){//task start
   //variable definition
  int capPos;
  float kp = 0.7;
  float kd = 1.5;
  int currentVal;
  int error;
  int error_last = 0;
  int error_diff;
  int power;

  while(true){ //loop infinitely
    if(master.get_digital(E_CONTROLLER_DIGITAL_B)){ //if the B Button is pressed
      if(CapButton.get_value()==HIGH){ //and the Limit Switch isn't pressed
          capTarget = 0; //move the arm down
          if(CapButton.get_value() == LOW){ //if the button is pressed
            capStack.move(0); //stop moving the arm
            capStack.tare_position(); //reset the encoder
          }
      }
    }
    else if((!master.get_digital(E_CONTROLLER_DIGITAL_L1)) //if not manual control (see opcontrol.cpp)
      &&(!master.get_digital(E_CONTROLLER_DIGITAL_L2))){
    capPos = capStack.get_position(); //current value is the built-in encoder position
    error = capTarget - capPos; //error is the Target Value (modified in opcontrol and auto) minus position
    error_diff = error - error_last; //difference of errors, used for the 'd' component of the PID
    error_last = error; //stores error for processing
    power = (error*kp)+(error_diff*kd); //output is the 'p' and 'd' sums - 'i' and feed forward are not used here
    if(power>capMax){power = capMax;} //the cap is the Maximum Value set in opcontrol and auto (as a global variable)
    if(power<-capMax){power = -capMax;} //the cap is the Minimum Value set in opcontrol and auto (as a global variable)
    if(error<2){capStack.move(0);} //if the error is small enough, don't move. This saves the motor strain.
    capStack.move(power); //move the motor
    delay(60);
  }
}
}
