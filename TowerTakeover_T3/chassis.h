#ifndef CHASSIS_H_
#define CHASSIS_H_
#include "main.h"

#define QUADRANT_1 1
#define QUADRANT_2 2
#define QUADRANT_3 3
#define QUADRANT_4 4

class Chassis{
public:

  void OP_Chassis(void);
  void MoveDistance(int direction, int targetValue, int timeout, int cap);
  void TurnDistance(int direction, int targetValue, int timeout);
  void TurnGyro(int direction, int targetValue, int timeout);
  void StrafeDistance(int direction, int targetValue, int timeout);
  void stopDriving(void);
  void driveOnAngle(double angle, int quadrant, int targetValue, int timeout);
};

#endif
