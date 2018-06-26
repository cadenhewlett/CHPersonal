#include "main.h"
#include "roller.h"
#include "functions.h"

void operatorControl() {
	while (true) {

		/*******************
		Joystick Drive Control
		********************/

		//Variable definition
		int deadzone = 12; //deadzone constant
		int X; //X Value
		int Y; //Y Value
		int JSV = joystickGetAnalog(1, 1); //Joystick Vertical Value
		int JSH = joystickGetAnalog(1, 3); //Joystick Horizontal Value

		//apply deadzone
		if(abs(JSV)>deadzone){Y = JSV;} //if the absolute value of the joystick vertical is greater than the deadzone, the y value stays the same
		else{Y = 0;} //if the joystick value is in the deadzone, it's value is not represented
		if(abs(JSH)>deadzone){X = JSH;} //if the absolute value of the joystick horizontal is greater than the deadzone, the x value stays the same
		else{X = 0;} //if the joystick value is in the deadzone, it's value is not represented

		cap(Y, 90); //use our cap function on the Y Value
		cap(X, 90); //use our cap function on the X Value

		//Left Drive
		motorSet(BaseFL, (Y+X));//Left Front
		motorSet(BaseBL, -(Y+X));//Left Back

		//Right Drive
		motorSet(BaseFR, (Y+X)); //Right Front
		motorSet(BaseBR, -(Y+X)); //Right Back

		/*******************
					Roller
		********************/
		 for (int speed = 25; joystickGetDigital(1, 6, JOY_UP); speed++) {  //initalize speed at 67, condition is 1, 6 up button, increment speed
			moveRoller(speed); //gradually ramps speed, even when it exceeds 127 cap sets it to 127
			delay(10); //delay 10 ms between each ramp
		}for (int speed = -25; joystickGetDigital(1, 6, JOY_DOWN); speed--) {
			moveRoller(speed); //ramps in the opposite direction
			delay(10); //delay 10ms
		}if((!joystickGetDigital(1, 6, JOY_DOWN))&&(!joystickGetDigital(1, 6, JOY_UP))){ //if not button 1, 6 up and not button 1, 6 down
			moveRoller(0); //dont move rollers
		}

delay(20);
	}//ends while loop
}//ends operator control
