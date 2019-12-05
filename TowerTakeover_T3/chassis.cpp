#include "main.h"
#include "chassis.h"
#include <cmath>
#include <iostream>

//Exponential Drive Function
int exponential (int joystickVal, float driveExp, int joyDead, int motorMin) { //e
		    int joySign;
		    int joyMax = 128 - joyDead;
		    int joyLive = abs(joystickVal) - joyDead;
		    if (joystickVal > 0) {joySign = 1;}
		    else if (joystickVal < 0) {joySign = -1;}
		    else {joySign = 0;}
		    int power = joySign * (motorMin + ((127 - motorMin) * (pow(joyLive, driveExp) / pow(joyMax, driveExp))));
		    return power;
}


void Chassis::OP_Chassis(void){
  int Ch3 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
	int Ch1 = exponential(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
  int Ch4 = exponential(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 1.5 /*DriveExp*/, 8 /*JoyDead*/, 15 /*MotorMin*/);
  /*BaseFL.move(-Ch3 - Ch1);
  BaseBL.move(-Ch3 - Ch1);
  BaseFR.move(Ch3 - Ch1);
  BaseBR.move(Ch3 - Ch1);*/

  BaseFL.move(-Ch3 - Ch1 - Ch4);
  BaseFR.move(-Ch3 - Ch1 + Ch4);
  BaseBL.move(Ch3 - Ch1 - Ch4);
  BaseBR.move(Ch3 - Ch1 + Ch4);

  /*
	ChassisMotors[BASE_FL_PORT].move(-Ch3 - Ch1 - Ch4);
  ChassisMotors[BASE_FR_PORT].move(-Ch3 - Ch1 + Ch4);
  ChassisMotors[BASE_BL_PORT].move(Ch3 - Ch1 - Ch4);
  ChassisMotors[BASE_BR_PORT].move(Ch3 - Ch1 + Ch4);
  */
}

void Chassis::stopDriving(void){
	BaseFL.move(0);
	BaseFR.move(0);
	BaseBL.move(0);
	BaseBR.move(0);
}

void Chassis::TurnDistance(int direction, int targetValue, int timeout){

		float driveKP = 0.7;
		float driveKD = 1.2;
	    //same PID Logic as turnValue
	    int motorPower;
	    int startTime = millis();
	    int currentValue = 0;
	    int err = 0;
	    int derr = 0;
	    int err_last = 0;
	    int err_sum = 0;
	    float KI = 0;
	    float p;
	    float i = 0;
	    float d;
			direction == DIRECTION_LEFT ? BaseFL.tare_position() : BaseFR.tare_position(); //resets left encoder if turning left, right if turning right
	    while((millis() - startTime) < timeout){

	      currentValue = abs(direction == DIRECTION_LEFT ? BaseFL.get_position() : BaseFR.get_position()); //gets left encoder if turning left, right if turning right
	      err = targetValue - currentValue;
	      err_last = err;
	      derr = (err - err_last);
	      p = (driveKP * err);
	      err_sum += err;
	      d = driveKD * derr;

	      motorPower = p+i+d;

	     /* if(motorPower > 90){motorPower = 90;} //cap speed at 90
	      if(motorPower < -90){motorPower = -90;} */
	      motorPower = (motorPower > 90 ? 90 : motorPower < -90 ? -90 : motorPower); //cap speed at +- 90 BUG : Needs test
	      BaseFL.move(direction*motorPower);
	      BaseFR.move((direction*motorPower));
	      BaseBL.move((direction*motorPower));
	      BaseBR.move(direction*motorPower);

	      delay(20);

	    }
}
void Chassis::MoveDistance(int direction, int targetValue, int timeout, int cap){

		float driveKP = 0.7;
		float driveKD = 1.2;
    //same PID Logic as turnValue
    int motorPower;
    int startTime = millis();
    int currentValue = 0;
    int err = 0;
    int derr = 0;
    int err_last = 0;
    int err_sum = 0;
    float KI = 0;
    float p;
    float i = 0;
    float d;
    BaseFL.tare_position();
    while((millis() - startTime) < timeout){

      currentValue = abs(BaseFL.get_position());
      err = targetValue - currentValue;
      err_last = err;
      derr = (err - err_last);
      p = (driveKP * err);
      err_sum += err;
      d = driveKD * derr;

      motorPower = p+i+d;

      if(motorPower > cap){motorPower = cap;}
      if(motorPower < -cap){motorPower = -cap;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      BaseFL.move(-direction*motorPower);
      BaseFR.move((direction*motorPower));
      BaseBL.move((-direction*motorPower));
      BaseBR.move(direction*motorPower);

      delay(20);

    }
}
void Chassis::TurnGyro(int direction, int targetValue, int timeout){

	float driveKP = 1.2;
	float driveKD = 0.8;

	gyro.reset();
	//initialize variables
	int motorPower; //motor power level
	int startTime = millis(); //Elapsed time since start of the sequence
	int currentValue = 0; //starting value of 0
	int turn_err = 0; //error value init
	int derr = 0;//error difference
	int err_last = 0; //last error
	int err_sum = 0; //sum of errors
	float KI = 0; //KI value - not currently used'
	float p; //p value normally 0.8
	float i = 0; //I value
	float d; //d value normally 0.7

	while((millis() - startTime) < timeout){
		currentValue = gyro.get_value();
		turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
		err_last = turn_err; //stores the error
		derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
		p = (driveKP * turn_err); //p value is preset driveKP multiplied by how far we are from our target
		err_sum += turn_err; //err_sum increases by the sum of errors
		d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

		motorPower = p+i+d; //motorpower is the sum of p, i, and d

		if(motorPower > 90){motorPower = 90;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
		if(motorPower < -90){motorPower = -90;}//if the motor power is less than -127 (the minimum it can go), set it to -127

			/*
				* Move motors the motorpower value times the direction.
				* Here, the Front Left motor and the Back Left motor are moving backwards if direction == 1
				* and the Back Right and Front Right motors are moving forwards if direction ==1
				* this is the setup that allows the base to turn
				*/
			BaseFL.move(direction*motorPower);
			BaseBL.move(direction*motorPower);
			BaseBR.move((direction*motorPower));
			BaseFR.move((direction*motorPower));

		delay(20);
	}

}
void Chassis::StrafeDistance(int direction, int targetValue, int timeout){

		float driveKP = 0.7;
		float driveKD = 1.2;
	    //same PID Logic as turnValue
	    int motorPower;
	    int startTime = millis();
	    int currentValue = 0;
	    int err = 0;
	    int derr = 0;
	    int err_last = 0;
	    int err_sum = 0;
	    float KI = 0;
	    float p;
	    float i = 0;
	    float d;
			direction == DIRECTION_LEFT ? BaseFL.tare_position() : BaseFR.tare_position(); //resets left encoder if turning left, right if turning right
	    while((millis() - startTime) < timeout){

	      currentValue = abs(direction == DIRECTION_LEFT ? BaseFL.get_position() : BaseFR.get_position()); //gets left encoder if turning left, right if turning right
	      err = targetValue - currentValue;
	      err_last = err;
	      derr = (err - err_last);
	      p = (driveKP * err);
	      err_sum += err;
	      d = driveKD * derr;

	      motorPower = p+i+d;

	     /* if(motorPower > 90){motorPower = 90;} //cap speed at 90
	      if(motorPower < -90){motorPower = -90;} */
	      motorPower = (motorPower > 90 ? 90 : motorPower < -90 ? -90 : motorPower); //cap speed at +- 90 BUG : Needs test
	      BaseFL.move(direction*motorPower);
	      BaseFR.move((direction*motorPower));
	      BaseBL.move(-(direction*motorPower));
	      BaseBR.move(-direction*motorPower);

	      delay(20);

	    }
}
void Chassis::driveOnAngle(double angle, int quadrant, int targetValue, int timeout){

		//PD Constants
  	float driveKP = 0.7;
  	float driveKD = 1.2;

    //General variables
    int motorPower;
    int startTime = millis();
    int currentValue = 0;
    int err = 0;
    int derr = 0;
    int err_last = 0;
    int err_sum = 0;
    float KI = 0;
		float p = 0;
		float i = 0;
		float d = 0;

		//Wheel modification values
		double FRMod;
		double FLMod;
		double BLMod;
		double BRMod;

		BaseFL.tare_position();
		BaseFR.tare_position();
		BaseBL.tare_position();
		BaseBR.tare_position();
		//Convert degree to radians
	//	angle = angle * (M_PI / 180);

		//Determine which qaudrant we're driving in
	/*
	if (angle < (M_PI / 2) && angle > 0 ) {
			quadrant = QUADRANT_1;
		}
		else if(angle < (M_PI) && angle > (M_PI / 2)) {
			quadrant = QUADRANT_2;
		}
		else if((angle < ((3*M_PI) / 2)) && angle > (M_PI)) {
			quadrant = QUADRANT_3;
		}
		else if(angle < (2*M_PI) && angle > (((3*M_PI) / 2))){
			quadrant = QUADRANT_4;
		}
*/
    while((millis() - startTime) < timeout){

			switch (quadrant) { //Change wheel modifications and enccder values based on the quadrant we're driving in.

				case 	QUADRANT_1 : //If we're driving in quadrant 1 (0 to π/2)
					currentValue = abs(BaseFR.get_position());
					FRMod = sin(angle - (M_PI/4));
					FLMod =  -1;
					BLMod = -sin(angle - (M_PI / 4));
					BRMod = 1;

				case QUADRANT_2 : //If we're driving in quadrant 1 (π/2 to π)
					currentValue = abs(BaseFL.get_position());
					FLMod = 1;
					FRMod = sin(angle - ((3*M_PI)/4));
					BRMod = 1;
					BLMod = sin(angle - ((3*M_PI)/4));

				case QUADRANT_3 : //BUG FL, BR might be Negative as well
					currentValue = abs(BaseBL.get_position());
					FLMod = 1;
					BLMod = -(sin(angle - (M_PI)/4));
					BRMod = -1;
					FRMod = (sin (angle - ((M_PI)/4)));


				case QUADRANT_4:
				/*BACK LEFT ALIGNMENT*/
					currentValue = abs(BaseBL.get_position());
					FLMod = 1;
					BLMod = -(sin(angle - (M_PI)/4));
					BRMod = -1;
					FRMod = (sin (angle - ((M_PI)/4)));
			}


      err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
      err_last = err; //stores the error
      derr = (err - err_last); //difference between how far you were from the target last sequence compared to this sequence
      p = (driveKP * err); //p value is preset driveKP multiplied by how far we are from our target
      err_sum +=  err; //err_sum increases by the sum of errors
      d = driveKD * derr; //d value is preset driveKD multiplied by the difference between how far you were from the last rotation

      motorPower = p+i+d; //motorpower is the sum of p, i, and d

      if(motorPower > 90){motorPower = 90;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
      if(motorPower < -90){motorPower = -90;}//if the motor power is less than -127 (the minimum it can go), set it to -127

			//moves the wheels according to the PID output and the Quadrant Modifications
      BaseFL.move(motorPower * FLMod);
      BaseBL.move(motorPower * BLMod);
      BaseBR.move(motorPower * BRMod);
      BaseFR.move(motorPower * FRMod);

      delay(20);
    }

}
