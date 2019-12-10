#include "main.h"
#include "lift.h"
#include "angler.h"

#include <string.h>

	Controller master(E_CONTROLLER_MASTER); //Main Controller
	Controller partner(E_CONTROLLER_PARTNER); //Partner Controller

	//Sensors
	ADIGyro gyro('b'); //Gyroscope
	Vision visionSensor(19); //Initialize Vision Sensor
	ADIDigitalIn button('a'); //A button that acts as a hard stop for the Angler
	ADIAnalogIn LightSensor('c');
	ADIAnalogIn TrayPot('d');
	ADIUltrasonic rightUlt('G', 'H'); //orange(ping), yellow(echo)
	ADIUltrasonic leftUlt('E','F');

	//Motors

	//#NOTE Broken Ports: 7, 2
	Motor BaseFL(12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Front Left Base Motor WAS 3
	Motor BaseFR(19, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Back Left Base Motor WAS 9
	Motor BaseBL(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Front Right Base Motor WAS 1
	Motor BaseBR(20, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Back Right Base Motor WAS 10
	Motor EmptyMotor(45,  E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //An Empty Motor, used as the default Test Motor
	Motor LiftL(4, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES); //The Arm Motor WAS 5
	Motor TrayMotor(5, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES); //the Tray Motor WAS 6
	Motor IntakeMotor(9, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES); //The left roller motor WAS 7
  Motor RollerMotor(3, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES); //The right roller motor WAS 4
	Motor LiftR(72,  E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Another Empty motor. Will be added in the program again if we ever switch back to a 2 motor lift

	//Motor Groups
	Motor ChassisMotors[4] = {BaseFL, BaseFR, BaseBL, BaseBR}; //Array of All Motors in the Chassis

	//Variables
	int currentAuto = NO_AUTO_SELECTED; //Current Auto (From the Auto Selector)
	int currentTestMotor = 0; //Current Motor Being Tested (From the Drop Down Menu)
	int presets[3] = {0, 500, 630}; //Array of presets for the Arm, which is used in lift.cpp
	int currentLiftPreset = 0; //A variable to store our current active preset (from above)
	int rollerSpeed = 0; //Roller Intake Global Speed

	//Classes
 	Display screen; //The Screen on the V5 Brain (from display.cpp)
	Chassis base; //The Base/Chassis of the Robot (from chassis.cpp)
	Camera camera; //A Vision Sensor object (from vision.cpp)

void initialize() {

	//Declare Our Tasks
	 Task Angler_Task (Angler_Task_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
	 			TASK_STACK_DEPTH_DEFAULT,	"Angler Task");

	 Task Lift_Task (Lift_Task_fn, (void*)"PROS", TASK_PRIORITY_DEFAULT,
 				TASK_STACK_DEPTH_DEFAULT, "Lift Task");

	 //Create the Screen
	 screen.createScreen(); //Creates the Items on the Screen. This is only called once.
}

void disabled() {}

void competition_initialize() {}
