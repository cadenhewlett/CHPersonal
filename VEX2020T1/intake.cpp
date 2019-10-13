#include "main.h"
#include "intake.h"

void Intake::opIntake(void){
  int targetPos;
  int motorPower; //motor power level
  int currentValue; //starting value of 0
  int err;
  int derr;//error difference
  int err_last; //last error
  int err_sum; //sum of errors
  float p ; //p value
  float i; //I value
  float d; //d value
  int count;
   if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && (toggled == false) && (count == 0)){
      toggled = true;
      count = 1;
      targetPos = 200;
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && (toggled == false) && (count == 1)){
      toggled = true;
      count = 0;
      targetPos = 0;
    }
    if(!(master.get_digital(E_CONTROLLER_DIGITAL_L1))){
      toggled = false;
    }

    currentValue = abs(IntakeMotor.get_position());
    err = targetPos - currentValue;
    err_last = err;
    derr = err - err_last;

    motorPower = (0.7 * err) + (1.2 * derr);
    motorPower = (motorPower > 127 ? 127: motorPower < -127 ? -127: motorPower); //cap speed at +- 127 BUG : Needs test

  /*  if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){motorPower = 90;}
      else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){motorPower = -90;}
      else{motorPower = 0;}
    */
      IntakeMotor.move(-motorPower);
}
