#include "main.h"
#include "lift.h"


void Lift::robotLift(void){
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

    if(master.get_digital(E_CONTROLLER_DIGITAL_X)){currentLiftPreset = 0;}
    else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){currentLiftPreset = 1;}
    else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){currentLiftPreset = 2;}
    else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){currentLiftPreset = 3;}

    targetPos = presets[currentLiftPreset];
    currentValue = abs(LiftL.get_position());
    err = targetPos - currentValue;
    err_last = err;
    derr = err - err_last;

    motorPower = (0.7 * err) + (1.2 * derr);
    motorPower = (motorPower > 127 ? 127: motorPower < -127 ? -127: motorPower); //cap speed at +- 127 BUG : Needs test

    LiftR.move(-motorPower);
    LiftL.move((motorPower));
}
