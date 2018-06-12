#include "main.h"

/*-----------------------------------------------------------------------------*/
/*  Set requested arm position and clip to limits                              */
/*-----------------------------------------------------------------------------*/

void SetArmPos(int position){
  if(position > ARM_UPPER_LIMIT){
    armTarget = ARM_UPPER_LIMIT;
  }
  else if(position < ARM_LOWER_LIMIT){
    armTarget = ARM_LOWER_LIMIT;
  }
  else{
    armTarget = position;
  }

/*-----------------------------------------------------------------------------*/
/*  Get requested arm position                                                 */
/*-----------------------------------------------------------------------------*/

}
int GetArmPos(void){
  return(armTarget);
}
/*-----------------------------------------------------------------------------*/
/*  arm p control task                                     */
/*-----------------------------------------------------------------------------*/
void ArmP(void*ignore){
  //variables
  int armCurrent;
  float armError;
  float armDrive;
  static float kp = 0.3;

  while( isEnabled()){
    if(armTarget > ARM_UPPER_LIMIT){armTarget = ARM_UPPER_LIMIT;}
    else if(armTarget < ARM_LOWER_LIMIT){armTarget = ARM_LOWER_LIMIT;}
    else{armTarget = armTarget;}
    //read sensor
    armCurrent = analogRead(armPot);
    //calculate error
    armError = armTarget - armCurrent;

    //calculate movement
    armDrive = (kp * armError);

    //limit drive
    if( armDrive > 127 ){armDrive = 127;}
    else if( armDrive < (-127) ){armDrive = (-127);}

    //send value to motor
    motorSet(armMotor, armDrive);

    //delay to not murder the CPU
    taskDelay(25);

  }
}

/*-----------------------------------------------------------------------------*/
/*  Wait for arm to be in position                                             */
/*  returns 1 on success or 0 on timeout                                       */
/*-----------------------------------------------------------------------------*/

short armWaitInPos(short timeout){
  //variables
  int armError;
  const int loopDelay = 50;
  //default timeout at 4 seconds
  if(timeout <= 0){timeout = 3000;}
  //convert mS to loops
  timeout /= loopDelay ;
  while(timeout >= 0){
    //small delay
    taskDelay(loopDelay);
    //get error
    armError = GetArmPos() - analogRead(armPot);
    //check the pid error for the arm
    if((abs(armError) < 50)){return(1);}
    //decrease the timeout
    timeout--;
  }
  return(0);
}
