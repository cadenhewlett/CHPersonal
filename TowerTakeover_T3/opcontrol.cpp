#include "main.h"

void opcontrol() {

	screen.setActiveTab(TAB_INFO);
	while (true) {

		base.OP_Chassis(); //Robot chassis OpControl Routine
		DR4B.anglerLift(); //Angle OpControl Routine
	  screen.refresh(); //Refresh the screen values
		DR4B.scrollerLift(); //The OpControl Lift and Roller Routine
	//	if(master.get_digital(E_CONTROLLER_DIGITAL_A)){camera.filterXVals(visionSensor.get_by_sig(0, GRN_CUBE));}
			//intake.opRollers();
		//	intake.opIntake();
		delay(30); //loop delay
	}
}
