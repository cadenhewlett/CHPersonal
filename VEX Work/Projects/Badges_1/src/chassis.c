#include "main.h"
#include "chassis.h"

void moveDrive(int LeftValue, int RightValue, int Cap){
  if(LeftValue > Cap){LeftValue = Cap;}
  if(LeftValue < -Cap){LeftValue = -Cap;}
  if(RightValue > Cap){RightValue = Cap;}
  if(RightValue < -Cap){RightValue = -Cap;}
  motorSet(motorL, LeftValue); //will have to change values later
  motorSet(motorR, RightValue);
  motorSet(motorLB, LeftValue);
  motorSet(motorRB, RightValue);
}
