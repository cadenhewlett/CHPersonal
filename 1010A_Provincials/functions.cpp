#include "functions.hpp"
#include "main.h"

void Functions::smartIntake(){
  bool toggled;
  while(!RollerLimit.get_value() && (toggled = false)){
    Roller.move(-127);
    if(RollerLimit.get_value() == LOW){
      Roller.move(0);
      toggled = true;
    }
    delay(50);
  }
}

void Functions::turnDegrees(int direction, int targetValue, int timeout, float KP, float KD){ //see function below for PID documentation
  int motorOutput;
  int outTime = millis();
  int err = 0;
  int derr = 0;
  int err_last = 0;
  int err_sum = 0;
  int currentValue = 0;
  float KI = 0;
  float p;
  float i;
  float d;
  //gyroM.reset();
  while((outTime - millis()) < timeout){
    currentValue = abs(gyroM.get_value());
    err = targetValue - currentValue;
    err_last = err;
    derr = (err - err_last);
    p = (KP * err);
    err_sum += err;
    d = KD * derr;

    motorOutput = p+i+d;
    if(motorOutput > 127){motorOutput = 127;}
    if(motorOutput < -127){motorOutput = -127;}

    BaseFL.move(motorOutput);
    BaseBL.move(motorOutput);
    BaseBR.move(-motorOutput);
    BaseFR.move(-motorOutput);

    delay(20);
  }
}
  void Functions::turnValue(int direction, int targetValue, int timeout, float KP, float KD){ //start turning function with inputs of direction, encoder values timeo kp and kd
    //initialize variables
    int motorPower; //motor power level
    int startTime = millis(); //start a timer
    int currentValue = 0; //starting value of 0
    int turn_err = 0; //error value init
    int derr = 0;//error difference
    int err_last = 0; //last error
    int err_sum = 0; //sum of errors
    float KI = 0; //KI value - not currently used'
    float p; //p value normally 0.8
    float i = 0; //I value
    float d; //d value normally 0.7
    BaseFL.tare_position(); //reset motor encoedr position
    while((millis() - startTime) < timeout){ //while [timer that starts on this line]-[timer that started outside the loop] is less than preset timeout value
      currentValue = abs(BaseFL.get_position()); //curent value is the absolute value of the motor encoder position
      turn_err = targetValue - currentValue; //error is how far the current position is from the position you put into the loop
      err_last = turn_err; //stores the error
      derr = (turn_err - err_last); //difference between how far you were from the target last sequence compared to this sequence
      p = (KP * turn_err); //p value is preset KP multiplied by how far we are from our target
      err_sum += turn_err; //err_sum increases by the sum of errors
      d = KD * derr; //d value is preset KD multiplied by the difference between how far you were from the last rotation

      motorPower = p+i+d; //motorpower is the sum of p, i, and d

      if(motorPower > 127){motorPower = 127;} //if the motor power is greater than 127 (the maximun it can go), set it to 127
      if(motorPower < -127){motorPower = -127;}//if the motor power is less than -127 (the minimum it can go), set it to -127

        /*
          * Move motors the motorpower value times the direction.
          * Here, the Front Left motor and the Back Left motor are moving backwards if direction == 1
          * and the Back Right and Front Right motors are moving forwards if direction ==1
          * this is the setup that allows the base to turn
          */
        BaseFL.move(-direction*motorPower);
        BaseBL.move(-direction*motorPower);
        BaseBR.move((direction*motorPower));
        BaseFR.move((direction*motorPower));

      delay(20);

    }
}
void Functions::stopEverything(){ //sets all the motor velocities to zero
  BaseFL.move(0);
  BaseFR.move(0);
  BaseBL.move(0);
  BaseBR.move(0);
  Roller.move(0);
  LinearLeft.move(0);
  LinearRight.move(0);
}
void Functions::stopDriving(){ //sets all the base motor velocities to zero (usseful for intake or shooting)
  BaseFL.move(0);
  BaseFR.move(0);
  BaseBL.move(0);
  BaseBR.move(0);
}
void Functions::strafeValue(int direction, int targetValue, int timeout, float KP, float KD){

  //same PID logic as turnValue
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
  BaseBL.tare_position();
  while((millis() - startTime) < timeout){
    if(direction == DIRECTION_RIGHT){currentValue = BaseFL.get_position();}
    else if(direction == DIRECTION_LEFT){currentValue = BaseBL.get_position();}
    err = targetValue - currentValue;
    err_last = err;
    derr = (err - err_last);
    p = (KP * err);
    err_sum += err;
    d = KD * derr;

    motorPower = p+i+d;

    if(motorPower > 127){motorPower = 127;}
    if(motorPower < -127){motorPower = -127;}

    /*
      * Move motors the motorpower value times the direction.
      * Here, the Front Left motor and the Back Right motor are moving backwards if direction == 1
      * and the Back Left and Front Right motors are moving forwards if direction ==1
      * this is the setup that allows the base to strafe
      */
      BaseFL.move(-direction*motorPower);
      BaseFR.move((direction*motorPower));
      BaseBL.move((direction*motorPower));
      BaseBR.move(-direction*motorPower);

    delay(20);

  }
}
  void Functions::driveValue(float direction, int targetValue, int timeout, float KP, float KD){

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
      p = (KP * err);
      err_sum += err;
      d = KD * derr;

      motorPower = p+i+d;

      if(motorPower > 127){motorPower = 127;}
      if(motorPower < -127){motorPower = -127;}
    //  motorPower = (motorPower > 1 ? 1 : motorPower < -1 ? -1 : motorPower);
      BaseFL.move(direction*motorPower);
      BaseFR.move((direction*motorPower));
      BaseBL.move((direction*motorPower));
      BaseBR.move(direction*motorPower);

      delay(20);

    }
}
void AutoDrive(int Mode, int direction, int targetValue, int timeout, float KP, float KD){
  //combination of driveValue, turnValue and strafeValue with a conditional called 'Mode' to switch between them
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
        if(direction == DIRECTION_RIGHT){currentValue = BaseFL.get_position();}
        else if(direction == DIRECTION_LEFT){currentValue = BaseBL.get_position();}
        err = targetValue - currentValue;
        err_last = err;
        derr = (err - err_last);
        p = (KP * err);
        err_sum += err;
        d = KD * derr;

        motorPower = p+i+d;

        if(motorPower > 127){motorPower = 127;}
        if(motorPower < -127){motorPower = -127;}
        switch(Mode){ //switches the positives and negatives based on the selected mode
          case 0:
          BaseFL.move(direction*motorPower);
          BaseFR.move((direction*motorPower));
          BaseBL.move((direction*motorPower));
          BaseBR.move(direction*motorPower);
          case 1:
          BaseFL.move(-direction*motorPower);
          BaseBL.move(-direction*motorPower);
          BaseBR.move((direction*motorPower));
          BaseFR.move((direction*motorPower));
          case 2:
          BaseFL.move(-direction*motorPower);
          BaseFR.move((direction*motorPower));
          BaseBL.move((direction*motorPower));
          BaseBR.move(-direction*motorPower);
        }

        delay(20);
    }
}
void Functions::fence(float kp, float kd, int timeout){

  //Variables
  int distR;
  int distL;
  int dist;
  int Lpower;
  int Rpower;

  //Start Timer
  int startTime = millis();

  //PID Align
  while((millis()-startTime)<timeout){
    distR = Ultrasonic_Right.get_value();
    distL = Ultrasonic_Left.get_value();
    int errorR = 130 - distR;
    int errorL = 130 - distL;
    int errorR_last = errorR;
    int errorL_last = errorL;
    int errorR_diff = errorR - errorR_last;
    int errorL_diff = errorL - errorL_last;

    Lpower = ((kp*errorL) + (kd *errorL_diff));
    Rpower = ((kp*errorR) + (kd * errorR_diff));

    BaseFL.move(Lpower);
    BaseBL.move(Lpower);
    BaseFR.move(Rpower);
    BaseBR.move(Rpower);
  }
    delay(20);
  }
