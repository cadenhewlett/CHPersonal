#include "main.h"
#include "lcd.h"
using namespace pros;

//exponential function: for gradual joystick modification, see link below for algorithm explanation
//NOTE: See https://sites.google.com/site/theonerobot/resources/exponential-drive-function
int exponential (int joystickVal, float driveExp, int joyDead, int motorMin) {
		    int joySign;
		    int joyMax = 128 - joyDead;
		    int joyLive = abs(joystickVal) - joyDead;
		    if (joystickVal > 0) {joySign = 1;}
		    else if (joystickVal < 0) {joySign = -1;}
		    else {joySign = 0;}
		    int power = joySign * (motorMin + ((100 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
		    return power;
		}

void opcontrol() { //starts main control loop
	
	capMax = 127; //changes maximum velocity of cap stacker, see capstack.cpp

	double startingPosition = angler.get_position(); //gets starting sensor values
	double startingPositionCap = capStack.get_position(); //gets starting sensor values

	//variables
	int count = 0;
  const int JoyDead = 8; // joystick range in which movement is considered accidental
  const int MotorMin = 15; // minimum drive motor power
  const float DriveExp = 1.5; // exponent for drive power calculations  (1 = linear, 2 = squared) //1.4

while(true){
	double AnglePosition = angler.get_position(); //gets the position of the angler

	int Ch3_p = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); //Left Joystick Y-Axis
	int Ch4_p = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_X); //Left Joystick X-Axis
	int Ch1_p = partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_X); //Right Joystick X-Axis
	//printf("%d\n", int(Ch3_p));
	int Ch3 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), DriveExp, JoyDead, MotorMin); //Left Joystick Y-Axis with Exponential
	int Ch4 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), DriveExp, JoyDead, MotorMin); //Left Joystick X-Axis with Exponential
	int Ch1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), DriveExp, JoyDead, MotorMin); //Right Joystick X-Axis with Exponential

	//move base motors in a mecanum drive format\
	//if any of the Axis on the Partner Controller are greater than the deadZone,
	//override the main controller analog input
	if((abs(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 10)|| //see above
			abs(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 10||
			abs(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_X)) > 10)
	{
	BaseFL.move((Ch3_p/2) + (Ch1_p/2) + (Ch4_p/2)); //half speed drive
	BaseBL.move((Ch3_p/2) + (Ch1_p/2) - (Ch4_p/2)); //half speed drive
	BaseFR.move((Ch3_p/2) - (Ch1_p/2) - (Ch4_p/2)); //half speed drive
	BaseBR.move((Ch3_p/2) - (Ch1_p/2) + (Ch4_p/2)); //half speed drive
}else //otherwise if the partner is not being controlled
	{
	BaseFL.move(Ch3 + Ch1 + Ch4); //standard mecanum drive
	BaseBL.move(Ch3 + Ch1 - Ch4); //standard mecanum drive
	BaseFR.move(Ch3 - Ch1 - Ch4); //standard mecanum drive
	BaseBR.move(Ch3 - Ch1 + Ch4); //standard mecanum drive
	}

//Linear Puncher Control
	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){ //if controller R1 is pressed
		LinearLeft.move(127); //move linear puncher
		LinearRight.move(-127);  //move linear puncher
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_R1)){ //else if controller R2 is pressed
		LinearLeft.move(127);  //move linear puncher
		LinearRight.move(-127);  //move linear puncher
	}else{
		LinearLeft.move(0);  //don't move linear puncher
		LinearRight.move(0);  //don't move linear puncher
	}
	//roller control
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){ //if button is pressed
		Roller.move(127); //move roller
	}else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){ //else if the other button is ressed
		Roller.move(-127); //move the other way
	}else{ //otherwise
		Roller.move(0); //don't move
	}

	//BELOW: Changes to Global Variable AngleTarget used in angler.cpp
	if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
		angleTarget = 154;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
		angleTarget = startingPosition;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
		angleTarget = 210;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
		angleTarget = 78;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
		angleTarget = 50;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
		angleTarget = 167;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
		angleTarget = 143;
	}
//	printf("%s", (LimitSwitch.get_value()) ? "true" : "false");

	//BELOW: Changes to Global Variable capTarget used in angler.cpp
	if(partner.get_digital(E_CONTROLLER_DIGITAL_L1)){
		capTarget += 50; //manual control (because the value increments)
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_L2)){
		capTarget -= 50; //manual control (because the value decrements)
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_X)){
		capTarget = 760;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_Y)){
		capTarget = 387;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_A)){
		capTarget = 815;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_B)){
		capTarget = 0;
	}

	//LCD Control of Motors
	if(!(master.is_connected())){ //only runs if controller is not connected
		if(LCD_Roller){
			Roller.move(-127 * LCD_Direction); //move the roller if button is selected on LCD, multiplied by the switch
			//Roller.move(currentSpeed);
		}else{
			Roller.move(0); //otherwise don't move roller
		}
		if(LCD_LP){
			LinearLeft.move(127); //linear puncher movement if  LCD option is selected
			LinearRight.move(127); //linear puncher movement if LCD option is selected
		}else{
			LinearLeft.move(0);
			LinearRight.move(0);
		}
		if(LCD_Angle){
		//	angleController.setTarget((startingPosition - 80)); //move angle controller if LCD option is selected
		}
		else{
		//  angleController.setTarget((startingPosition)); //otherwise set posiiton to default
		}
	}

	pros::delay(100); //loop delay
}
}
