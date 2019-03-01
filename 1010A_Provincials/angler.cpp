    #include "main.h"
 #include "angler.h"

 void ANGLE_Task_fn(void*parameter){
   int anglePos;
   float kp = 0.7;
   float kd = 1.5;
   int currentVal;
   int error;
   int error_last = 0;
   int error_diff;
   int power;
   int count = 0;
   while(true){
   if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
       count = 0;
       if(LimitSwitch.get_value() == false){
         angler.move(-67);
         if(LimitSwitch.get_value() == true){
           if(count == 0){
           //master.rumble("-.-");
           delay(750);
           count += 1;
           }
           angler.tare_position();
          // startingPosition = 0;
           angleTarget = 0;
         }
       }
     }
    // printf("%d \n", angleTarget);
     anglePos = angler.get_position();
     error = angleTarget - anglePos;
     error_diff = error - error_last;
     error_last = error;
     power = (error*kp)+(error_diff*kd);
    // if(error<3){angler.move(0);}
      angler.move(power);
   }

   delay(20);
   }
