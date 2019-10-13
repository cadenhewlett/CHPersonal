#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"
#include <stdio.h>
#include <errno.h>


#define SWITCH_FORWARD true
#define PC_FILES 1
#define NO_AUTO_SELECTED 0

class Display{
public:
  void setActiveTab(int tab);
  void createScreen(void);
  void createGauge(void);
  void createTabs(void);
  void createOpLEDs(void);
  void createBackground(void);
  void create1010Image(void);
  void createSwitch(void);
  void createTitle(void);
  void createAutoSelector(void);
  void createMotorTest(void);
  void createBatteryMeter(void);
  void refresh(void);
  void motorTest(void);

};


#endif
