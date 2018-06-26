#ifndef MAIN_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define MAIN_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
  #define BaseFL 1
  #define BaseBL 2
  #define BaseFR 3
  #define BaseBR 4
  #define RollerR 5
  #define RollerL 6

  Gyro gyro;
  Encoder EncoderL;
  Encoder EncoderR;

#endif
void autonomous();
void initializeIO();
void initialize();
void operatorControl();

#ifdef __cplusplus
}
#endif

#endif
