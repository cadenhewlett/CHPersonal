#include "main.h"
#include "lift.h"

void Lift_Task_fn(void * parameter){
  int err = 0;
  int err_last = 0;
  int i = 0;
  int armValue = 0;
  int armPower= 0;
  int derr = 0;
  int currentTarget;
  bool armToggled = false;
  bool slowTake = true;

  //This is split into two segments: Roller and Lift. Some functionalities of one are dependent
  //on the other, so they are both programmed in this file to make their interactions more dynamic.

  while(true){

    /*******************************
    ************* LIFT *************
    ********************************/

    if(competition::is_autonomous()){
      currentTarget = armAutoTarget; //sets target to manually control.ed 'auto' target
      if(currentTarget == CUBE_LIFT_PRESET){ //if we're doing a cube lift thing
        currentTarget = presets[1]; //go to mid preset
        slowTake = true; //and activate the 'slowTake' procedure
      }
      else{
        slowTake = false; //otherwise don't slowTake
      }
    }

    else{ //'Scroll Wheel' Style of Preset Selection

      if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && armToggled == false){ //if L1 change target value to 300
        i += 1; //increment our current preset state
        armToggled = true; //a button has been toggled
        slowTake = false; //we are not intaking briefly
      }

      else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && armToggled == false){ //if L2 then change target to 110
        i -= 1; //decrement our current preset state
        armToggled = true; //a button has been toggled
        slowTake = false; //we are not intaking briefly
      }

      if(master.get_digital(E_CONTROLLER_DIGITAL_X) && armToggled == false){ //if X then move to first index and move intake slightly
        i = 1; //move to middle state
        slowTake = true; //starts our small cube intake process (see below)
      }

      if(i > 2){i = 0;} //if the index of our presets is too high, return it to start
      else if(i < 0){i = 2;}//if the index is too low, return it to the top

      if(!master.get_digital(E_CONTROLLER_DIGITAL_L1) && !master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_X)){
        armToggled = false; //resets the toggled variable if none of the buttons are pressed. This helps prevent double clicking.
      }

      currentTarget = presets[i]; //target value is the index of the presets array in initialize.cpp
    }

    armValue = abs(LiftL.get_position()); //current value equals encoder reading

    err = currentTarget - armValue; //err equals target value minus current position
    err_last = err; //stores last err
    derr = err - err_last; //determines the change of err in one rotation

    armPower = (0.8 * err) + (1.2 * derr); //output equals sum of 'p' multiplied by its constant and 'd' multiplied by its constant
    armPower = (armPower > 127 ? 127 : armPower < -127 ? -127 : armPower); //caps speed at +- 127

    LiftL.move(-armPower);

    /*******************************
    ********** ROLLERS *************
    ********************************/

    if(!(competition::is_autonomous())){ //if we're not in auto
      if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //if R1 is pressed
        rollerSpeed = -127; //set speed to -127
      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){ //otherwise if R2 is pressed
        rollerSpeed = 127;  //set speed to 127
      }
      else if(slowTake){ //if we're slowtaking
         if(armValue < 200){ //while armValue is less than 200
           rollerSpeed = 67; //set speed to 67
         }
         else{ //once value is greater than 200
           rollerSpeed = 0; //stop moving the rollers
         }
      }
      else{ //if no buttons are pressed
        rollerSpeed = 0; //set speed to 0
      }
    }
    else if(competition::is_autonomous()){ //if we're in auto
      if(slowTake){ //if we're slowtaking
        if(armValue < 200){
          rollerSpeed = 67; //while armValue is less than 200 set speed to 67
        }
        else{//once value is greater than 200
          rollerSpeed = 0; //set speed to 0
        }
      }
      else{ //if we're not slowtaking
        rollerSpeed = rollerSpeed; //set speed to whatever I've manually set it to be in autonomous.cpp
      }
    }
  }
  IntakeMotor.move(rollerSpeed); //move roller motors according to rollerSpeed
  RollerMotor.move(rollerSpeed); //move roller motors according to rollerSpeed
}
