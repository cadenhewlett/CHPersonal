#include "main.h"
#include "flywheel.h"
#include "lcd.h"
//#include "variables.h"

using namespace okapi;

void opcontrol() {
	//pros::Task my_cpp_task (FW_Task);

	okapi::Controller controller;

  ControllerButton FW_MAX(ControllerDigital::up);
	ControllerButton FW_SLOW(ControllerDigital::right);
  ControllerButton FW_MED(ControllerDigital::left);
	ControllerButton FW_ZERO(ControllerDigital::down);

	ControllerButton runAutoButton(ControllerDigital::X);
		//roller buttons
	ControllerButton Roller_IN(ControllerDigital::R2);
	ControllerButton Roller_OUT(ControllerDigital::R1);
		//flipper buttons
	ControllerButton Flip_IN(ControllerDigital::A);
	ControllerButton Flip_OUT(ControllerDigital::Y);
	//inside roller read_button
	ControllerButton Inside_IN(ControllerDigital::L2);
	ControllerButton Inside_OUT(ControllerDigital::L1);
//	pros::Controller partner(pros::E_CONTROLLER_PARTNER);

	//Initialize motor on port 4
//	okapi::Motor FWheel = 3_mtr;

	auto drive = ChassisControllerFactory::create(
		{1, 2}, // Left motors
		{-9, -10},   // Right motors
		AbstractMotor::gearset::red, // Torque gearset
		{3.25_in, 12.5_in} // 4 inch wheels, 12.5 inch wheelbase width
	);
	auto profileController = AsyncControllerFactory::motionProfile(
		1.0,  // Maximum linear velocity of the Chassis in m/s
		2.0,  // Maximum linear acceleration of the Chassis in m/s/s
		10.0, // Maximum linear jerk of the Chassis in m/s/s/s
		drive // Chassis Controller
	);
	 auto flipper = AsyncControllerFactory::posIntegrated(7);
   auto flywheelController = AsyncControllerFactory::velIntegrated(3);


//  Motor Flipper = 7_mtr;
	okapi::Motor InsideRoller = 6_mtr; //use rmtr for invert
	okapi::Motor Roller = 5_mtr;
  bool firstpressed = false;
  okapi::Motor Flipper = 7_mtr;
	while (true) {
	//	pros::lcd::print(1, "%d", pros::c::joystickGetAnalog(pros::E_CONTROLLER_PARTNER, pros::E_CONTROLLER_ANALOG_LEFT_Y));
	//	pros::lcd::print(2, "%d", partner.get_digital(pros::E_CONTROLLER_DIGITAL_A));
	//	pros::lcd::print(3, "%d", partner.is_connected());
	/*	pros::lcd::print(4, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
*/
	  drive.arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX));

//		controllerBAT = "Batt: %d", controller.getBatteryLevel(); //string variable for holding battery level
//		controller.setText(1, 0, controllerBAT); //set controller line 1 to controller battery leve
 /*if(FW_MAX.isPressed()){
	  flywheelController.setTarget(-127);
		}
	else if(FW_MED.isPressed()){
		flywheelController.setTarget(-100);
	}
	else if(FW_SLOW.isPressed()){
		flywheelController.setTarget(-50);
	}
	else if(FW_ZERO.isPressed()){
		flywheelController.setTarget(0);
	}*/


		/******************
		    CAP FLIPPER
		*******************/

		if(Flip_IN.isPressed()){
			Flipper.move(90);
			firstpressed = true;
		}
		else if((Flip_OUT.isPressed())&&(firstpressed = true)){ //else if a button is pressed
			Flipper.move(-90);
		}
		else{
			Flipper.move(0);
		}

		/******************
		      ROLLER
		*******************/
		if (Roller_IN.isPressed()) { //if L1 button is pressed
				Roller.move(-127);//move roller full power
		}
		else if (Roller_OUT.isPressed()) { // else if L2 is pressed
				Roller.move(127);//move roller full power other way
		}
		else { //otherwise don't move roller
				Roller.move(0);
			}

			/******************
			   INSIDE ROLLER
			*******************/
		if (Inside_IN.isPressed()) {//if R1 button is pressed
				InsideRoller.move(90);//move inside roller full power
		}
		else if (Inside_OUT.isPressed()) {//if R2 button is pressed
				InsideRoller.move(-90);//move roller other way
		}
		else {//otherwise don't move
				InsideRoller.move(0);
		}
		if(!(controller.isConnected())){
			if(LCD_Roller == true){
				Roller.move(-127 * LCD_Direction);
				//Roller.move(currentSpeed);
			}if(LCD_InsideRoller == true){
				InsideRoller.move(127 * LCD_Direction);
				//flywheelController.setTarget(-(currentSpeed));
			}

		}
		pros::delay(20);
	}
}
