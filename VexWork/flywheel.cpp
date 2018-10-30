#include "main.h"
#include "lcd.h"
void FW_Task_fn(void*parameter){
  using namespace pros;
// 	pros::Controller partner(pros::E_CONTROLLER_PARTNER);
  //Initialize Buttons

  okapi::Controller controller;
  okapi::ControllerButton FW_MaxButton(ControllerDigital::up);
  okapi::ControllerButton FW_ZeroButton(ControllerDigital::down);
  okapi::ControllerButton FW_Stall(ControllerDigital::right);
  okapi::ControllerButton FW_Medium(ControllerDigital::left);
  //Initialize motor on port 4
  okapi::Motor FWheel = 3_mtr;
  okapi::Motor FWheel2 = 4_mtr;

  //Initialize Variables
  int i = 00;
  int cap = 0;
  int speed;
  int delay_val = 30;
  while(true){ //task never ends
    for(speed = i; true; speed ++){//increments s by 1 each iteration
        //if not autonomous
        //lcd::print(1, "Flywheel Voltage: %d", FWheel.getPower()); //send value to screen
        //lcd::print(0, "Flywheel Speed: %d", (s-1));
        if(pros::competition::is_autonomous()){
          cap = 127;
        }
        else if(FW_MaxButton.isPressed() || ((LCD_FWheelMax)&&(LCD_FWheelOff == false)) /*partner.get_digital(pros::E_CONTROLLER_DIGITAL_UP)*/){ //if up arrow button is pressed
          cap = 127; //set target to max
          controller.clearLine(1);
          controller.setText(1, 0, "Flywheel at:127");
        }
        else if(FW_Medium.isPressed() || ((LCD_FWheelMed)&&(LCD_FWheelOff == false))/*partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)*/){ //if left arrow button is pressed
          cap = 85; //set target to medium speed
          controller.clearLine(1);
          controller.setText(1, 0, "Flywheel at:85");
        }
        else if(FW_Stall.isPressed() || ((LCD_FWheelLow)&&(LCD_FWheelOff == false)) /*partner.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)*/){ //if right arrow button is pressed
          cap = 50; //set target to cruise speed
          controller.clearLine(1);
          controller.setText(1, 0, "Flywheel at::50");
        }
        else if(FW_ZeroButton.isPressed()/*partner.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)*/){//if down arrow button is pressed
          cap  = 0; //stop the flywheel
          controller.clearLine(1);
          controller.setText(1, 0, "Flywheel at:0");
        }
        if(speed > cap){speed = cap;} //if ramped speed is greater than the cap it becomes the cap
        FWheel.move(-speed); //move the flywheel at the speed value
        FWheel2.move(speed);
        delay(delay_val); //delay for the delay value
      }
    }
    delay(5);
  }
