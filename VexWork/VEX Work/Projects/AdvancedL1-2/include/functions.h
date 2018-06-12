#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void AutoDrive(bool direction, int targetValue, int timeout);
void AutoTurn(bool forward, int targetValue, int timeout, float KP, float KD);

#endif
