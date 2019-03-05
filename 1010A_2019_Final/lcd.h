#ifndef _LCD_H_
#define _LCD_H_
#include "pros/apix.h"

void LCD_Task_fn(void * parameter);
static lv_res_t switch_action(lv_obj_t * swtch);
static lv_res_t autoSelect_action(lv_obj_t * roller);
static lv_res_t cb_release_action(lv_obj_t* cb);
static lv_res_t fw_cb_release_action(lv_obj_t * FWcb);
static lv_res_t btn_click_action(lv_obj_t * btn);
static lv_res_t ddlist_action(lv_obj_t * ddlist);
extern int currentAuto;
extern int currentSpeed;
extern int LCD_Direction;
extern bool LCD_Roller;
extern bool LCD_LP;
extern bool LCD_Angle;

#endif
