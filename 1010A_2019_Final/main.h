#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
#include "pros/apix.h"
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"
//#include "pros/adi.h"
using namespace pros;
///static constants
#define BALL_YLW 1

#define Base_FR 9 //base motor front right port
#define Base_FL 1 //base motor front left port
#define Base_BR 10 //base motor back right port
#define Base_BL 2 //base motor front right port
#define DIRECTION_LEFT 1 //direction constant used in functions.cpp functon strafeValue and turnValue
#define DIRECTION_RIGHT -1  //direction constant used in functions.cpp functon strafeValue and turnValue
#define DIRECTION_FORWARD 1  //direction constant used in functions.cpp functon driveValue
#define DIRECTION_BACKWARD -1  //direction constant used in functions.cpp functon driveValue
#define AnglerPORT 7 //linear puncher angler port
#define CapPORT 11

#define MODE_DRIVE 0
#define MODE_TURN 1
#define MODE_STRAFE 2

//extrnal variables for motors, sensors and controllers
extern int angleTarget;
extern int capTarget;
extern int linearTarget;
extern int capMax;
//for initialization, see initialize.cpp
extern Controller master;
extern Controller partner;

extern pros::Motor BaseFL;
extern pros::Motor BaseBL;
extern pros::Motor BaseFR;
extern pros::Motor BaseBR;
extern pros::Motor LinearLeft;
extern pros::Motor LinearRight;
extern pros::Motor Roller;
extern pros::Motor angler;
extern pros::Motor InsideRoller;
extern pros::Motor capStack;

extern pros::Vision vSensor;
extern pros::ADIGyro gyroM;
extern pros::ADIDigitalIn LimitSwitch;
extern pros::ADIDigitalIn CapButton;
extern pros::ADIDigitalIn RollerLimit;
extern pros::ADIUltrasonic Ultrasonic_Left;
extern pros::ADIUltrasonic Ultrasonic_Right;

//opcontrol data
extern double AnglePosition;
extern double AngleTarget;
extern float opTime;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}


#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
