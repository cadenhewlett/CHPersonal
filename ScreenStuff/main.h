#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#define NO_AUTO_SELECTED 0
#define RED_FRONT 1
#define BLUE_FRONT 2
#define RED_BACK 3
#define BLUE_BACK 4
#define SKILLS_AUTO 5

#include "api.h"
#include "pros/apix.h"
#include "display.h"
using namespace pros;

extern ADIDigitalIn button;
extern ADIAnalogIn LightSensor;
extern ADIGyro gyro;
extern Display screen;
extern int currentAuto;
extern Motor testMotor;


extern lv_obj_t*tabs;
extern lv_obj_t*auto_op_tab;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*test_tab;
extern lv_obj_t*gyroGauge;
extern lv_obj_t * frontLED;


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
#endif
