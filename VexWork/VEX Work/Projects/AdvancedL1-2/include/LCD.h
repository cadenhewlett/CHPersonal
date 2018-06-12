#ifndef LCD_H_
#define LCD_H_

#include "main.h"

extern int currentAuto;

void LCD_Teleop(void*ignore);
TaskHandle LCD_Teleop_task;

void LCD_Disabled(void*ignore);
TaskHandle LCD_Disabled_task;

void LCD_Auto(void*ignore);
TaskHandle LCD_Auto_task;



#endif
