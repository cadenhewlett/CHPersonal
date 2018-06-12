#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void ArmP(void*ignore);
TaskHandle ArmP_task;
void SetArmPos(int position);
int GetArmPos(void);
long GetCurrentTime(void);
short armWaitInPos(short timeout);
#endif
