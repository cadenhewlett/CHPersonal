#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

//direction variables
#define DIRECTION_FORWARD 1
#define DIRECTION_BACKWARD -1
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT -1

//auto variables
#define NO_AUTO_SELECTED 0
#define RED_FRONT 1
#define BLUE_FRONT 2
#define RED_BACK 3
#define BLUE_BACK 4
#define SKILLS_AUTO 5

#include "api.h"
#include "pros/apix.h"
#include "chassis.h"
#include "display.h"
#include "intake.h"
#include "lift.h"

using namespace pros;

#define BASE_FL_PORT 2 //Front Left Base Motor Port
#define BASE_FR_PORT 9 //Front Right Base Motor Port
#define BASE_BL_PORT 1 //Back Left Base Motor Port
#define BASE_BR_PORT 10 //Back Right Base Motor Port

#define TAB_DISPLAY 0
#define TAB_INFO 1
#define TAB_TEST 2

extern Controller master;
extern ADIDigitalIn button;
extern ADIAnalogIn LightSensor;
extern ADIGyro gyro;
extern int currentAuto;
extern int currentTestMotor;
extern Motor testMotor;
extern Motor othertestMotor;

extern Chassis base;
extern Display screen;
extern Lift DR4B;
extern Intake intake;

extern int currentLiftPreset;
extern int presets[4];
extern Motor ChassisMotors[4];
extern Motor SystemMotors[7];

extern Motor BaseFL;
extern Motor BaseFR;
extern Motor BaseBL;
extern Motor BaseBR;
extern Motor LiftL;
extern Motor LiftR;
extern Motor IntakeMotor;
extern Motor EmptyMotor;

extern lv_obj_t*tabs;
extern lv_obj_t*auto_op_tab;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*test_tab;
extern lv_obj_t*gyroGauge;
extern lv_obj_t*frontLED;
extern lv_obj_t*motorSelect;
extern lv_obj_t*OnOffSwitch;
extern lv_obj_t*directionSwitch;
extern lv_obj_t*sys_battery_meter;
extern lv_obj_t*bat_meter_label;
extern lv_obj_t*symbol_label;
extern lv_obj_t*gyroLabel;

extern bool toggled;
extern bool fwd;
extern bool off;

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
