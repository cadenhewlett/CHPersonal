#ifndef VISION_H_
#define VISION_H_

#include "main.h"

#define GRN_CUBE 1
#define ORN_CUBE 3
#define PPL_CUBE 2

class Camera{
public:

  int getNearestSig(void);
  int getObjectXVal(int objectSig);
  int getObjectYVal(int objectSig);
  int getObjectWidth(int objectSig);
  int getObjectHeight(int objectSig);
  void centerToObject(int objectSig, int targetValue /*Will not be needed eventually*/, int timeout);

};

#endif
