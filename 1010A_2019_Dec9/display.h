#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"
#include <stdio.h>
#include <errno.h>


#define SWITCH_FORWARD true
#define PC_FILES 1
#define NO_AUTO_SELECTED 0
#define AUTO_UNPROTEC_BLUE 1
#define AUTO_UNPROTEC_RED 2
#define AUTO_SKILLS 3
class Display{
public:
  void setActiveTab(int tab);
  void createBars(void);
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
