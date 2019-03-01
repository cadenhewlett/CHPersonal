#include "main.h"
#include "lcd.h"
using namespace pros;
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
		static lv_res_t autoSelect_action(lv_obj_t * roller) //Auto selection roller action function
		{
		  currentAuto = lv_roller_get_selected(roller); //current auto becomes the integer ID of the selected value
		                                                //this means that if "None" is selected, this will be ID 0
		  return LV_RES_OK; //return an OK Status after execution
		}
void opcontrol() {
	capMax = 127;
	double startingPosition = angler.get_position();
	double startingPositionCap = capStack.get_position();

	auto capController = okapi::AsyncControllerFactory::posIntegrated(CapPORT);
	auto angleController = okapi::AsyncControllerFactory::posIntegrated(AnglerPORT);

	//variables
	int count = 0;
  const int JoyDead = 8; // joystick range in which movement is considered accidental
  const int MotorMin = 15; // minimum drive motor power
  const float DriveExp = 1.5; // exponent for drive power calculations  (1 = linear, 2 = squared) //1.4

while(true){
	double AnglePosition = angler.get_position();

	int Ch3_p = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); //Left Joystick Y-Axis
	int Ch4_p = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_X); //Left Joystick X-Axis
	int Ch1_p = partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_X); //Right Joystick X-Axis
	//printf("%d\n", int(Ch3_p));
	int Ch3 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), DriveExp, JoyDead, MotorMin); //Left Joystick Y-Axis
	int Ch4 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), DriveExp, JoyDead, MotorMin); //Left Joystick X-Axis
	int Ch1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), DriveExp, JoyDead, MotorMin); //Right Joystick X-Axis

	//move base motors
	if((abs(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) > 10)||
			abs(partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) > 10||
			abs(partner.get_analog(E_CONTROLLER_ANALOG_LEFT_X)) > 10)
	{
	BaseFL.move((Ch3_p/2) + (Ch1_p/2) + (Ch4_p/2));
	BaseBL.move((Ch3_p/2) + (Ch1_p/2) - (Ch4_p/2));
	BaseFR.move((Ch3_p/2) - (Ch1_p/2) - (Ch4_p/2));
	BaseBR.move((Ch3_p/2) - (Ch1_p/2) + (Ch4_p/2));
}else
	{
	BaseFL.move(Ch3 + Ch1 + Ch4);
	BaseBL.move(Ch3 + Ch1 - Ch4);
	BaseFR.move(Ch3 - Ch1 - Ch4);
	BaseBR.move(Ch3 - Ch1 + Ch4);
	}
//vision_color_code_t ccRedFlag = vSensor.create_color_code(0, 1);
//pros::vision_signature_s_t RED_SIG = Vision::signature_from_utility(2, 8973, 11143, 10058, -2119, -1053, -1586, 5.4, 0);
	auto current_colour = vSensor.get_signature(0);

	vision_object_s_t red = vSensor.get_by_sig(0, 2);
	printf("Left UTR %d \n", Ultrasonic_Left.get_value());
	printf("Right UTR %d \n", Ultrasonic_Right.get_value());
	if(abs(red.x_middle_coord) == 32224){
	//	printf("No object detected! \n");
	}else{
//	printf("Red Object XPos: %d \n", red.x_middle_coord);
//	printf("Red Object XPos, FILTERED %d \n", vision.visionFilterX(0, 2));
//	printf("Red Object YPos: %d \n", red.y_middle_coord);
}

/*	if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
		RoboVision roboVision;
		roboVision.Align_to_Object(BALL_YLW, 0, 0, 0.7, 0.8, 0.001);
	}
	//Use below to fix  presets if angleController is moved out of position
	if(master.get_digital(E_CONTROLLER_DIGITAL_X)){ //if x button is pressed
			if(LimitSwitch.get_value() == HIGH){
				angler.move(-60);
				count = 0; //reset count
			}
			else if(LimitSwitch.get_value() == LOW){
				angler.move(0);
				startingPosition = 0; //angler.get_position()
				if(count == 0){ // if the count is currently zero
				//master.rumble(". - . -"); //rumble controller to let driver know that the position has reset
				delay(250); //delay
			//	master.rumble(". - . -"); //rumble again (not needed)
				count = 1; //count increments so that rumble isn't forever
			}
			}
		}
*/
//Linear Puncher Control
	if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
		LinearLeft.move(127);
		LinearRight.move(-127);
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_R1)){
		LinearLeft.move(127);
		LinearRight.move(-127);
	}else{
		LinearLeft.move(0);
		LinearRight.move(0);
	}
	//roller control
	if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){ //if button is pressed
		Roller.move(127); //move roller
	}else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){ //else if the other button is ressed
		Roller.move(-127); //move the other way
	}else{ //otherwise
		Roller.move(0); //don't move
	}

	//linear puncher angler
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
		angleTarget = 147;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
		angleTarget = 131;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
		angleTarget = 50;
	}
	else if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
		angleTarget = 143;
	}
//	printf("%s", (LimitSwitch.get_value()) ? "true" : "false");
	//cap stacker
	if(partner.get_digital(E_CONTROLLER_DIGITAL_L1)){
		capTarget += 35;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_L2)){
		capTarget -= 35;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_X)){
		capTarget = 760;
	}
	else if(partner.get_digital(E_CONTROLLER_DIGITAL_Y)){
		capTarget = 384;
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

	pros::delay(100);
}
}
