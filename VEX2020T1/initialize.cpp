#include "main.h"
#include "intake.h"
	Controller master(E_CONTROLLER_MASTER); //Main Controller

	//Sensors
	ADIGyro gyro('d'); //Gyroscope

	ADIDigitalIn button('h');
	ADIAnalogIn LightSensor('f');


	Motor BaseFL(BASE_FL_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Front Left Base Motor
	Motor BaseFR(BASE_FR_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Back Left Base Motor
	Motor BaseBL(BASE_BL_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Front Right Base Motor
	Motor BaseBR(BASE_BR_PORT, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Back Right Base Motor
	Motor EmptyMotor(11,  E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
	Motor LiftL(5, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	Motor LiftR(6, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
	Motor IntakeMotor(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);

	Motor ChassisMotors[4] = {BaseFL, BaseFR, BaseBL, BaseBR}; //Array of All Motors in the Chassis
	Motor SystemMotors[7] = {EmptyMotor, BaseFL, BaseFR, BaseBL, BaseBR, LiftR, LiftL}; //Array of All Motors Intialized on our V5 System
	//Classes and variables
	int currentAuto = NO_AUTO_SELECTED; //Current Auto (From the Auto Selector)
	int currentTestMotor = 0; //Current Motor Being Tested (From the Drop Down Menu)
	int presets[4] = {75, 400, 600, -45};
	int currentLiftPreset = 0;
	bool toggled = false;
	//Lift DR4B;
 	Display screen; //The Screen on the V5 Brain
	Chassis base; //The Base/Chassis of the Robot
  Lift DR4B;
	Intake intake;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
   screen.createScreen(); //Creates the Items on the Screen
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
