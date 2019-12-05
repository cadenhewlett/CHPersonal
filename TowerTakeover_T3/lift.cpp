#include "main.h"
#include "lift.h"

  //define variables
  int armTarget = 0;
  int armValue = 0;

  int i = 0;
  int j = 0;
  int targetPos = 0;
  int motorPower = 0;
  int joyStickMod = 0;
  int currentValue = 0;
  int cap = 127;
  int err;
  int derr;
  int err_last;
  int err_sum;
  int A_err;
  int A_derr;
  int A_err_last;
  int armPower;

  bool slowTake = false;
  bool armToggled = false;
  bool wasManual = false;
  bool presetChanged = false;
  bool buttonStop = false;


void Lift::scrollerLift(void){

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

//Implemented control of the Intake using an additional 'slowTake' boolean
//slowTake briefly intakes the cube when we lift using option 'X', so that
//the mechanism that keeps the tower in place can work properly

//Standard OpControl movement of Intake
  if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
    IntakeMotor.move(-127); //move Intake according to the speed
    RollerMotor.move(-127);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
    IntakeMotor.move(127); //move Intake according to the speed
    RollerMotor.move(127);
  }

  else if((slowTake)){ //this is the 'slowTake' that secures the cube when ewe're lifting
    if(abs(LiftL.get_position()) < 200){ //for the first part of our lifting
      IntakeMotor.move(67); //move the intake
      RollerMotor.move(67);
    }
    else{
      IntakeMotor.move(0); //then stop
      RollerMotor.move(0);
    }
  }
  else{
    IntakeMotor.move(0); //standard opcontrol movement of rollers
    RollerMotor.move(0);
  }


  armTarget = abs(presets[i]);  //our target value is the 'index' we are scrolling to from the array presets[3] ininitialize.cpp

  armValue = abs(LiftL.get_position()); //target equals intake motor position

  A_err = armTarget - armValue; //err equals target minus current value
  A_err_last = A_err; //store last error
  A_derr = A_err - A_err_last; //error difference is the delta of the errors

  armPower = (0.8 * A_err) + (1.2 * A_derr); //output equals sum of  KP x I_err and KD x dI_err: PD Loop
  armPower = (armPower > 127 ? 127: armPower  < -127 ? -127: armPower); //cap speed at +- 127

  LiftL.move(-armPower); //move the arm motor according to PD output

}

void Lift::anglerLift(void){

      if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
        targetPos = -5;
        buttonStop = true;

      }
      else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
        targetPos = 535; //was 615
        currentLiftPreset = 1;//changes the index of the target value
        buttonStop = false;
      }

      currentValue = abs(TrayMotor.get_position()); //takes the absolute value of the right lift motor encoder

      if((targetPos == 535) && (currentValue > 200)){ //was 615
        cap = 60;
      }
      else{
        cap = 127;
      }

      //if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 0){joyStickMod +=1;}
  //    targetPos = wasManual ? currentValue : presets[currentLiftPreset];

      wasManual = (abs(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 1.2 /*deadzone*/); //if the Joystick Value is greater than the deadzone, the lift is/was in manual control
      err = targetPos - currentValue; //error is difference between target and current
      err_last = err; //store last error
      derr = err - err_last; //determine the difference of errors
      motorPower = (0.7 * err) + (1.2 * derr); //multiply error and error differencce by our kp and kd constants
      motorPower = (motorPower > cap ? cap: motorPower < -127 ? -127: motorPower); // caps the upward speed, for preset 1 - no cap for downward speed because of the button

      if(buttonStop && (button.get_value() == HIGH)){ //if our active stop variable is true AND the digital button is pressed
        //  TrayMotor.tare_position(); //reset encoder value
        TrayMotor.move(0);
      }
        else{
          TrayMotor.move(-motorPower); //move the lift equal to motorPower, meaning standard PID movement
        }
      }


void Lift::robotLift(void){

/*
*The Robot Lift runs primarily on three conditions. The first condition is the state of the machine: manual or preset.
*This is the boolean 'wasManual'. The second condition is judged based on the previous condition. If the control is not
*manual, moreover, it is running with presets, the second condition will determine if we have arrived at our preset,
*and if the preset has changed. See the boolean 'presetChanged'. The next condition is put forward by the digital buttonStop
*at the bottom of the lift. If this button is pressed, and the preset or manual is moving downwards, the lift will stop moving.
*this is to ensure that there is no damage to the machine. See the boolean 'buttonStop'. The heirachy of these conditions is as
*follows: 'wasManual', 'presetChanged', 'buttonStop' if the lift is moving pased on the presets. If the lift is moving manually,
*the heirachy is: 'wasManual', 'buttonStop', 'presetChanged'.
*/
    if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
      currentLiftPreset = 3; //changes the index of the target value
      presetChanged = true;
      buttonStop = true;
      cap = 45; //caps the speed to reduce the risk of dropping a cube
    }
    else if(partner.get_digital(E_CONTROLLER_DIGITAL_X)) {
      currentLiftPreset = 4; //changes the index of the target value
      presetChanged = true;
      buttonStop = true;
      cap = 127; //no speed cap

    }
    else if(partner.get_digital(E_CONTROLLER_DIGITAL_Y)){
      currentLiftPreset = 2; //changes the index of the target value
      presetChanged = true;
      buttonStop = false;
      cap = 127; //no speed cap
    }
    else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
      currentLiftPreset = 1;//changes the index of the target value
      presetChanged = true;
      buttonStop = false;
      cap = 127; //no speed cap
    }
    else if(partner.get_digital(E_CONTROLLER_DIGITAL_B)){
      currentLiftPreset = 0;
      presetChanged = true;
      buttonStop = false;
      cap = 127; //no speed cap
    }

    //if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 0){joyStickMod +=1;}
//    targetPos = wasManual ? currentValue : presets[currentLiftPreset];

    currentValue = abs(LiftR.get_position()); //takes the absolute value of the right lift motor encoder

    targetPos = presetChanged ? presets[currentLiftPreset] : currentValue; //if the preset was changed, make the target the new preset, otherwise hold position.
                                                                           //This was made so that the presets don't interfere with the manual control

    wasManual = (abs(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) > 1.2 /*deadzone*/); //if the Joystick Value is greater than the deadzone, the lift is/was in manual control

    if(wasManual){ //if manual control
      if(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < -1.2){ //if the lift is moving downwards
        buttonStop = true; //changed the buttonStop to be true, so that we don't hurt the lift. See later.
      }
      presetChanged = false; //Since we're manual, the preset isn't changing.
      if(buttonStop && (button.get_value() == HIGH)){ //if our active stop variable is true AND the digital button is pressed
        LiftR.tare_position(); //reset the right encoder value
        LiftR.move(0); //stop moving the lift
        LiftL.move(0);
      }
      else{ //if our safety is not active
      LiftR.move(-partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)); //move the lift equal to the joystick value
      LiftL.move((partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));
      }
    }
    else{ //if we're not in manual control, run the PID for the presets

      err = targetPos - currentValue; //error is difference between target and current
      err_last = err; //store last error
      derr = err - err_last; //determine the difference of errors

      motorPower = (0.7 * err) + (1.2 * derr); //multiply error and error differencce by our kp and kd constants
      motorPower = (motorPower > cap ? cap: motorPower < -127 ? -127: motorPower); // caps the upward speed, for preset 1 - no cap for downward speed because of the button
      if(buttonStop && (button.get_value() == HIGH)){ //if our active stop variable is true AND the digital button is pressed
        LiftR.tare_position(); //reset encoder value
        LiftR.move(10); //move the lift down very slowly to lock into position
        LiftL.move(-10);
      }
      else{
        LiftR.move(-motorPower); //move the lift equal to motorPower, meaning standard PID movement
        LiftL.move((motorPower));
      }
    }
}
void Lift::autoAngler(int targetValue, int timeout){

  int err = 0;
  int err_last = 0;
  int currentValue;
  int motorPower;
  int cap;
  int derr;
  int startTime = millis();

  while((millis() - startTime) < timeout){

    armValue = abs(TrayMotor.get_position()); //target equals intake motor position

    //if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 0){joyStickMod +=1;}
  //    targetPos = wasManual ? currentValue : presets[currentLiftPreset];
    if((targetValue == 520) && (armValue > 245)){
      cap = 60;
    }
    else{
      cap = 127;
    }
    armTarget = targetValue;


    A_err = armTarget - armValue; //err equals target minus current value
    A_err_last = A_err; //store last error
    A_derr = A_err - A_err_last; //error difference is the delta of the errors

    armPower = (0.8 * A_err) + (1.2 * A_derr); //output equals sum of  KP x I_err and KD x dI_err: PD Loop
    armPower = (armPower > cap ? cap: armPower  < -cap ? -cap: armPower); //cap speed at +- 127

    TrayMotor.move(-armPower);

    delay(20);
  }

}

void Lift::autoLift(int targetValue, int timeout, bool FancyLift){ //PID with timeout for auto. Uses similar logic to the presets in opcontrol (see above)

  int err = 0;
  int err_last = 0;
  int currentValue = 0;
  int armPower= 0;
  int derr = 0;
  int startTime = millis();

  while((millis() - startTime) < timeout){


    currentValue = abs(LiftL.get_position()); //target equals intake motor position

    //if(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > 0){joyStickMod +=1;}
  //    targetPos = wasManual ? currentValue : presets[currentLiftPreset];
  //FancyLift determines if we're doing the cool score arm with tower stack thing.
  //It moves the roller motors while the Left Position is less than 200
    if(armValue < 200 && FancyLift){
      IntakeMotor.move(67); //move the intake
      RollerMotor.move(67);
    }
    else{
      IntakeMotor.move(0); //move the intake
      RollerMotor.move(0);
    }

    err = targetValue - currentValue; //err equals target minus current value
    err_last = err; //store last error
    derr = err - err_last; //error difference is the delta of the errors

    armPower = (0.8 * err) + (1.2 * derr); //output equals sum of  KP x I_err and KD x dI_err: PD Loop
    armPower = (armPower > 127 ? 127: armPower  < -127 ? -127: armPower); //cap speed at +- 127

    LiftL.move(-armPower);

    delay(20);
  }

}
