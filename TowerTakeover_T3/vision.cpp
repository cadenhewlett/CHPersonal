#include "main.h"
#include "vision.h"
#include <string.h>

int Camera::getObjectXVal(int objectSig){

  vision_object_s_t object = visionSensor.get_by_sig(0, objectSig);
  return object.x_middle_coord;

}

int Camera::getNearestSig(void){
  vision_object_s_t biggestObject = visionSensor.get_by_size(0);
  return biggestObject.signature;
}

int Camera::getObjectYVal(int objectSig){

  vision_object_s_t object = visionSensor.get_by_sig(0, objectSig);
  return object.y_middle_coord;
}

int Camera::getObjectWidth(int objectSig){
  vision_object_s_t object = visionSensor.get_by_sig(0, objectSig);
  return object.width;
}

int Camera::getObjectHeight(int objectSig){
  vision_object_s_t object = visionSensor.get_by_sig(0, objectSig);
  return object.height;
}

void Camera::centerToObject(int objectSig, int targetValue, int timeout){

  float driveKP = 0.2; //constants //was 0.7
  float driveKD = 0.4; //was 1.2
  float driveKI = 0.009;
    //same PID Logic as turnValue in chassis.cpp
  int motorPower;
  int startTime = millis();
  int currentValue = 0;
  int err = 0;
  int derr = 0;
  int err_last = 0;
  int err_sum = 0;

  float p;
  float i = 0;
  double direction = 1;
  float d;
  vision_object_s_t object = visionSensor.get_by_sig(0, objectSig);
  screen.setActiveTab(TAB_INFO);

  while((millis() - startTime) < timeout){
    screen.refresh();
    object = visionSensor.get_by_sig(0, objectSig);

    currentValue = object.x_middle_coord;

    err = targetValue - currentValue;  //err equals target minus current value
    err_last = err; //store last error
    p = (driveKP * err);

    err_sum += err; //increment error sum
    i = driveKI * err_sum;

    derr = (err - err_last); //error difference is the delta of the errors
    d = driveKD * derr;

    motorPower = p+i+d; //output equals sum of  KP x I_err and KD x dI_err: PD Loop

    motorPower = (motorPower > 67 ? 67 : motorPower < -67 ? -67 : motorPower); //cap speed at +- 90


    if(abs(err) > 200){ ///if error greater than +- 200
      direction = 0; //THERE'S A PROBLEM OH GOD MAKE IT STOP
    }
    else{ //otherwise
      direction = 1; //it's all good. We're alive. For now...
    }

    ChassisMotors[BASE_FL_INDEX].move(-motorPower * direction);
    ChassisMotors[BASE_BL_INDEX].move(motorPower * direction);
    ChassisMotors[BASE_FR_INDEX].move(-motorPower * direction);
    ChassisMotors[BASE_BR_INDEX].move(motorPower * direction);
    delay(20);
  }

}
