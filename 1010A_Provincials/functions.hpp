#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include "main.h"
class Functions {
public:
void smartIntake();
void fence(float kp, float kd, int timeout);
void AutoDrive(int Mode, int direction, int targetValue, int timeout, float KP, float KD);
void turnDegrees(int direction, int targetValue, int timeout, float KP, float KD);
void turnValue(int direction, int targetValue, int timeout, float KP, float KD);
void strafeValue(int direction, int targetValue, int timeout, float KP, float KD);
void driveValue(float direction, int targetValue, int timeout, float KP, float KD);
void stopEverything();
void stopDriving();
};
#endif
