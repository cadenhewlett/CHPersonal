#include "main.h"

void opcontrol() {

	screen.setActiveTab(TAB_INFO);
	while (true) {

		base.OP_Chassis(); //Robot chassis OpControl Routine
	  screen.refresh(); //Refresh the screen values

	}
}
