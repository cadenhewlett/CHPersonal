 #include "main.h"
 #include "angler.h"
 /*
 This is a PID Controller for the Linear Puncher Angle Controller that
 is running as a permanent tasks. The target of this controller is changed
 by changing the global variable 'angleTarget' in any location. This task is
 started in initialize.cpp and is referenced in opcontrol.cpp and autonomous.cpp
 NOTE: See PID Controller: https://en.wikipedia.org/wiki/PID_controller
 */
 void ANGLE_Task_fn(void*parameter){ //task start
   //variable definition
   int anglePos;
   float kp = 0.7;
   float kd = 1.5;
   int currentVal;
   int error;
   int error_last = 0;
   int error_diff;
   int power;
   int count = 0;

   while(true){ //loop infinitely
   if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){ //if down button: Hard Reset
       count = 0; //variable that controls rumble
       if(LimitSwitch.get_value() == false){ //if the switch is up
         angler.move(-67); //move the angler down
         if(LimitSwitch.get_value() == true){ //when the limit switch id pressed
           if(count == 0){ //rumble the controller to notify the driver
           //master.rumble("-.-");
           delay(750);
           count += 1; //increment so it doesn't rumble continuously
           }
           angler.tare_position(); //reset the encoder
          // startingPosition = 0;
           angleTarget = 0; //reset the target
         }
       }
     }
     anglePos = angler.get_position(); //current value is the built-in encoder position
     error = angleTarget - anglePos; //error is the Target Value (modified in opcontrol and auto) minus position
     error_diff = error - error_last; //difference of errors, used for the 'd' component of the PID
     error_last = error; //stores error for processing
     power = (error*kp)+(error_diff*kd); //output is the 'p' and 'd' sums - 'i' and feed forward are not used here
    // if(error<3){angler.move(0);}
      angler.move(power); //move the angler equal to the pd sum
      delay(60); //loop delay
   }
   }
