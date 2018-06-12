#include "main.h"
#include "chassis.h"

void moveDrive(int LeftValue, int RightValue, int Cap){
  if(LeftValue > Cap){LeftValue = Cap;}
  if(LeftValue < -Cap){LeftValue = -Cap;}
  if(RightValue > Cap){RightValue = Cap;}
  if(RightValue < -Cap){RightValue = -Cap;}
  motorSet(2, LeftValue); //will have to change values later
  motorSet(1, RightValue);
//  motorSet(motorLB, LeftValue);
//  motorSet(motorRB, RightValue);
}
