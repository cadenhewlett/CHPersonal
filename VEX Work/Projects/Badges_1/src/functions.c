#include "main.h"
#include "chassis.h"


void AutoTurn(bool L, int targetValue, int timeout, float KP, float KD){
  int direction;
  if(L){direction = 1;} //if Left is true, direction is 1
    else{direction = -1;}//else -1
  //declare variables and reset sensors
  int motorOutput;
  int err = 0;
  int derr = 0;
  int err_last = 0;
  int err_sum = 0;
  int currentValue = 0;
  float outTime = millis();
  float KI = 0; //currently KI is 0
  float p;
  float i;
  float d;
  gyroReset(gyro);


  while(outTime- millis() > timeout){//while timeout is not achieved

    currentValue = abs(gyroGet(gyro)); //value is absolute gyro value
    err = targetValue - currentValue; //error is target minus current
    err_last = err; //last error is eqaul to the last documented error
    derr = err - err_last; //err difference is equal to the difference between last documented error and error
    p = KP * err; //Proportional is equal to KP Input multiplied by error
    err_sum = err_sum + err; //combined sum of errors
    d = KD * derr; //Derivitive is equal to KD Input times the error difference
    if(err<7){i = KI * err_sum;} //if the error is greater than 7, Integral


    motorOutput = p+i+d;

    int leftside = direction * motorOutput; //direction multiplier
    int rightside = -(direction * motorOutput);//direction multiplier

    moveDrive(leftside, rightside, 127);
    delay(50);
  }
}

void AutoDrive(bool direction, int targetValue, int timeout){

  //variables
  int mult;
  int LPower;
  int RPower;

  //direction control -- true is forward, false is backwards
  if(direction){mult = 1;}
  if(!direction){mult = -1;}

  int EncAvg = 0; //reset value
  encoderReset(EncoderL); //reset encoder
  encoderReset(EncoderR); //reset encoder

  float startTime = millis(); //starting time for timeout

  while(EncAvg < targetValue || (millis()-startTime)<timeout) { //while encoder average is less than target, or timeout
    EncAvg = (abs(encoderGet(EncoderL)) + abs(encoderGet(EncoderR))) / 2; //average of encoder values
    if(EncAvg < targetValue){//when target is not achieved
      LPower = 127; //full power
      RPower = 127;
    }else{//when target is achieved
      LPower = 0; //no power
      RPower = 0;
    }
    //drives left and right motors, multiplied by the direction with a cap of 127
    moveDrive((LPower * mult), (RPower * mult), 127);

  }
}
