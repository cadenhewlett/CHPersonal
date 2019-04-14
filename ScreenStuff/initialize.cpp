#include "main.h"

	ADIGyro gyro('g');
	ADIDigitalIn button('h');
	ADIAnalogIn LightSensor('f');
	Motor testMotor (10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	int currentAuto = NO_AUTO_SELECTED;
 	Display screen;

//	std::string autoOptions[3] = {"fwd", "bckwd", "stop"} ;

void initialize() {
		screen.createHomeScreen();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
