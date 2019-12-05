#include "main.h"
#include "intake.h"

int IntakePower = 0; //motor power level

void Intake::opIntake(void){

		 if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
			 IntakePower = 127;
		 }
		 else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
			 IntakePower = -127;
		 }
		 else{
			 IntakePower = 0;
		 }


/*
	 if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){ //if L1 change target value to 300
		 IntakeTarget = 300;
	 }
	 else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){ //if L2 then change target to 110
		 IntakeTarget = 110;
	 }
	 else{ //otherwise return target to 0
		 IntakeTarget = 0;
	 }

   IntakeValue = abs(IntakeMotor.get_position()); //target equals intake motor position
   I_err = IntakeTarget - IntakeValue; //err equals target minus current value
   I_err_last = I_err; //store last error
   dI_err = I_err - I_err_last; //error difference is the delta of the errors

   IntakePower = (0.7 * I_err) + (1.2 * dI_err); //output equals sum of  KP x I_err and KD x dI_err: PD Loop
   IntakePower = (IntakePower > 127 ? 127: IntakePower < -127 ? -127: IntakePower); //cap speed at +- 127
*/
   IntakeMotor.move(-IntakePower); //move Intake according to the speed
	 RollerMotor.move(-IntakePower);
}

void Intake::autoIntake(int speed){
	IntakeMotor.move(-speed); //move Intake according to the speed
	RollerMotor.move(-speed);
}
void Intake::opRollers(void){

  if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //move roller if R1
    RollerMotor.move(127);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){ //nove back if R2
    RollerMotor.move(-127);
  }
  else{ //otherwise don't move
    RollerMotor.move(0);
  }

}
