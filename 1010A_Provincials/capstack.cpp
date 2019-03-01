#include "main.h"
#include "angler.h"

void CAPSTACK_Task_fn(void*parameter){
  int capPos;
  float kp = 0.7;
  float kd = 1.5;
  int currentVal;
  int error;
  int error_last = 0;
  int error_diff;
  int power;
  while(true){
    if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
      if(CapButton.get_value()==HIGH){
          capTarget = 0;
          if(CapButton.get_value() == LOW){
            capStack.move(0);
            capStack.tare_position();
          }
      }
    }
    else if((!master.get_digital(E_CONTROLLER_DIGITAL_L1))&&(!master.get_digital(E_CONTROLLER_DIGITAL_L2))){
    capPos = capStack.get_position();
    error = capTarget - capPos;
    error_diff = error - error_last;
    error_last = error;
    power = (error*kp)+(error_diff*kd);
    if(power>capMax){power = capMax;}
    if(power<-capMax){power = -capMax;}
    if(error<2){capStack.move(0);}
    capStack.move(power);
  }
}
}
