#ifndef _VISION_H_
#define _VISION_H_
#include "main.h"
class VisionFunctions {
public:
  void visionAlign(int sig);
  bool flagTargets(int sig);
  int visionFilterX(int size, int sig);
};

#endif
