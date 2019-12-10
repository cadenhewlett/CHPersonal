#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#define _USE_MATH_DEFINES

#include "api.h"
#include "pros/apix.h"
#include "chassis.h"
#include "lift.h"
#include "angler.h"
#include "display.h"
#include "vision.h"

using namespace pros;
//Direction Constants
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD -1
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT -1

//Preset Special Case
#define CUBE_LIFT_PRESET 4

//Ports
#define BASE_FL_PORT 2 //Front Left Base Motor Port
#define BASE_FR_PORT 1 //Front Right Base Motor Port
#define BASE_BL_PORT 9 //Back Left Base Motor Port
#define BASE_BR_PORT 10 //Back Right Base Motor Port

//Screen Tabs
#define TAB_DISPLAY 0
#define TAB_INFO 1
#define TAB_TEST 2

//Autonomous Routines, From Selector
#define NO_AUTO_SELECTED 0
#define RED_FRONT 1
#define BLUE_FRONT 2
#define RED_BACK 3
#define BLUE_BACK 4
#define SKILLS_AUTO 5

//Global Variables

//Variables Modified in Tasks
extern int armAutoTarget;
extern int anglerAutoTarget;
extern int rollerSpeed;
extern int currentLiftPreset;

//Variables Modified in Display
extern int currentAuto;
extern int currentTestMotor;

//Constants
extern int presets[3];
extern Motor ChassisMotors[4];
extern Motor SystemMotors[7];
extern bool toggled;
extern bool fwd;
extern bool off;

//Controllers
extern Controller master;
extern Controller partner;

//Sensors
extern ADIDigitalIn button;
extern ADIAnalogIn TrayPot;
extern ADIAnalogIn LightSensor;
extern ADIGyro gyro;
extern ADIUltrasonic rightUlt;
extern ADIUltrasonic leftUlt;
extern Motor testMotor;
extern Motor othertestMotor;
extern Vision visionSensor;

//Subsystems/Objects
extern Chassis base;
extern Display screen;
extern Camera camera;

//Motors
extern Motor BaseFL;
extern Motor BaseFR;
extern Motor BaseBL;
extern Motor BaseBR;
extern Motor LiftL;
extern Motor LiftR;
extern Motor IntakeMotor;
extern Motor EmptyMotor;
extern Motor RollerMotor;
extern Motor TrayMotor;

//Screen Objects
extern lv_obj_t*tabs;
extern lv_obj_t*auto_op_tab;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*motor_test_tab;
extern lv_obj_t*frontLED;
extern lv_obj_t*backLED;
extern lv_obj_t*lftLED;
extern lv_obj_t*fnlLED;
extern lv_obj_t*motorBar1;
extern lv_obj_t*motorLabel1;
extern lv_obj_t*motorBar2;
extern lv_obj_t*motorLabel2;
extern lv_obj_t*sys_battery_meter;
extern lv_obj_t*bat_meter_label;
extern lv_obj_t*symbol_label;
extern lv_obj_t*gyroGauge;
extern lv_obj_t * autoSelector;
extern lv_obj_t*motorSelect;
extern lv_obj_t*OnOffSwitch;
extern lv_obj_t*directionSwitch;
extern lv_obj_t *visionObjectLabel;
extern lv_obj_t*gyroLabel;


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
