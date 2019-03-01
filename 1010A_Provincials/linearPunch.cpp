#include "linearPunch.h"
#include "main.h"

/*
* This task is running simultaneously to opcontrol.cpp, and is initialized in initialize.cpp
* The intention of this task is to develop a 'smart' system for the Liear Puncher, with
* manual control and a loading mechanism for full extension of the Puncher
*/
void LP_Task_fn(void*parameter){

  int linearPos;
  int revolutionTarget = 0;
  int revDiff = 0;
  float kp = 0.7;
  float kd = 1.5;
  int currentVal;
  int error;
  int error_last = 0;
  int error_diff;
  int power;
  while(true){
    linearPos = LinearRight.get_position(); //gets the current position of the motor encoder
    if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //if the R1 Button is pressed
      linearTarget += 25; //manually increment the position
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){//otherwise if the R2 Button is pressed
      revolutionTarget +=  500; //increment the *revolution* target by the value of one full rotation
      revDiff = linearPos - revolutionTarget; //compare the current positionn to the revolution target
      linearTarget = revolutionTarget + revDiff; //equate the values
    }
    error = linearTarget - linearPos; //error is the target minus the current. This will always be positive b/c of the logic above
    error_diff = error - error_last; //difference in errors
    error_last = error; //stores the error
    power = (error*kp)+(error_diff*kd); //PID value
    LinearRight.move(power); //move the LP motor
    delay(35); //loop delay
  }
}
