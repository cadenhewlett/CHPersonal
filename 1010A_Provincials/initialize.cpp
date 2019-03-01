#include "main.h"
#include "lcd.h"
#include "angler.h"
#include "capstack.h"

using namespace pros;

			Controller master(E_CONTROLLER_MASTER);
			Controller partner(E_CONTROLLER_PARTNER);
			//motors
		  Motor BaseFL (16, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Port 1 Not Reversed, Green Gearbox Reading in Degrees //10
			Motor BaseBL (17, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Port 2 Not Reversed, Green Gearbox Reading in Degrees //9
		 //Right
			Motor BaseFR (15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Port 9 Reversed, Green Gearbox Reading in Degrees//1
			Motor BaseBR (14, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Port 10 Reversed, Green Gearbox Reading in Degrees //2
			//Angler
			//Linear Puncher
		  Motor LinearLeft(2, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES); //Port 5 Reversed, Red Gearbox Reading in Degrees
			Motor LinearRight(18, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES); //Port 6 Not Reversed, Red Gearbox Reading in Degrees
			//Rollers
			Motor Roller(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);//Port 4 Not Reversed, Green Gearbox Reading in Degrees
			//Motor InsideRoller(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
			//angler
			pros::Motor angler(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Port 1 Not Revers
      pros::Motor capStack(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

			//sensors
			Vision vSensor(13);
			ADIUltrasonic Ultrasonic_Left('d', 'g'); //init ultrasonic: Orange is 'd', Yellow is 'e'
			ADIUltrasonic Ultrasonic_Right('b', 'c');  //init ultrasonic: Orange is 'b', Yellow is 'c'
			ADIDigitalIn LimitSwitch('e'); //limit switch plugged into 'f'
      ADIDigitalIn CapButton('f');
			ADIDigitalIn RollerLimit('a');
			ADIGyro gyroM('h', 1);// gyro plugged in to 'a' with a multiplier of 1

			//variables for the background PID Tasks
      int angleTarget = 0;
      int capTarget = 0;
			int linearTarget = 0;
			int capMax = 0;
void initialize() {
	gyroM.reset();
	vSensor.clear_led();
	vSensor.set_zero_point(E_VISION_ZERO_CENTER);

	vision_signature_s_t GREENFLAG;
    GREENFLAG.id = 2;
    GREENFLAG.range = 2.8;
    GREENFLAG.u_min = -3383;
    GREENFLAG.u_max = -2431;
    GREENFLAG.u_mean = -2907;
    GREENFLAG.v_min = -4711;
    GREENFLAG.u_max = -2891;
    GREENFLAG.v_mean = -3801;
    GREENFLAG.type = 0;


	//set brake modes
	BaseFL.set_brake_mode(E_MOTOR_BRAKE_COAST); //hold position
	BaseBL.set_brake_mode(E_MOTOR_BRAKE_COAST); //hold position
	BaseFR.set_brake_mode(E_MOTOR_BRAKE_COAST); //hold position
	BaseBR.set_brake_mode(E_MOTOR_BRAKE_COAST); //hold position
	Roller.set_brake_mode(E_MOTOR_BRAKE_COAST); //brake after movement, coast afterwards
	LinearLeft.set_brake_mode(E_MOTOR_BRAKE_COAST); //no brake
	LinearLeft.set_brake_mode(E_MOTOR_BRAKE_COAST);//no brake

	/*pros::Task LCD_Task(
				LCD_Task_fn,
				(void*)"PROS",
				TASK_PRIORITY_DEFAULT,
				TASK_STACK_DEPTH_DEFAULT,
				"LCD Task"
			);*/
   pros::Task ANGLE_Task(
        ANGLE_Task_fn,
        (void*)"PROS",
        TASK_PRIORITY_DEFAULT,
        TASK_STACK_DEPTH_DEFAULT,
        "Angle Task"
   );
	 pros::Task CAP_Task(
        CAPSTACK_Task_fn,
        (void*)"PROS",
        TASK_PRIORITY_DEFAULT,
        TASK_STACK_DEPTH_DEFAULT,
        "Cap Task"
   );
/*   pros::Task LCD_Task(
         LCD_Task_fn,
         (void*)"PROS",
         TASK_PRIORITY_DEFAULT,
         TASK_STACK_DEPTH_DEFAULT,
         "LCD Task"
       );
       */
}
void disabled() {

}

void competition_initialize() {}
