#ifndef DISPLAY_H
#define DISPLAY_H
#include "main.h"
#include <stdio.h>
#include <errno.h>


#define SWITCH_FORWARD true
#define PC_FILES 1

class Display{
public:

  void createGauge(void);
  void createTabs(void);
  void createOpLEDs(void);
  void createBackground(void);
  void imageTest(void);
  void imageTest2(void);
  void createSwitch(void);
  void createTitle(void);
  void createAutoSelector(void);
  void createHomeScreen(void);
  void refresh(void);

};


#endif
