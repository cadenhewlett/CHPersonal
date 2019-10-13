#ifndef CHASSIS_H_
#define CHASSIS_H_
#include "main.h"

class Chassis{
public:

  void OP_Chassis(void);
  void MoveDistance(int direction, int targetValue, int timeout);
  void TurnDistance(int direction, int targetValue, int timeout);
  void TurnGyro(int direction, int targetValue, int timeout);
  void stopDriving(void);
};

#endif
