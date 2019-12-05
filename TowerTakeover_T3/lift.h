#ifndef LIFT_H_
#define LIFT_H_
#include "main.h"

class Lift{

public:
//  using Lift::Lift;
  void anglerLift(void);
  void scrollerLift(void);
  void initLift(void);
  void robotLift(void);
  void autoLift(int targetValue, int timeout, bool FancyLift);
  void autoAngler(int targetValue, int timeout);
};

#endif
