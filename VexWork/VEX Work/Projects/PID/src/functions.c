#ifdef FUNCTIONS_C_
#define FUNCTIONS_C_


void turn(bool forward, int targetValue, int timeout, float KP, float KD){
  int direction;
  if(forward){direction = 1;}
    else{direction = -1;}
  int outTime = millis();
  int err = 0;
  int derr = 0;
  int err_last = 0;
  int err_sum = 0;
  int currentValue = 0;
  float KI = 0;
  float p;
  float i;
  float d;
  gyroReset(Bob);

  while(outTime- millis() > timeout || (targetValue =/= currentValue)){

    currentValue = abs(gyroGet(Bob));
    err = targetValue - currentValue;
    err_last = err;
    derr = err - err_last;
    p = KP * err;
    err_sum = err_sum + err;
    d = KD * derr;
    if(error<7){i = KI * err_sum;}


    motorOutput = p+i+d;

    if(motorOutput > 127){motorOutput = 127;}
    if(motorOutput < -127){motorOutput = -127;}

    int leftside = direction * motorOutput;
    int rightside = -(direction * motorOutput);
    delay(50);
  }
  delay(15);
}
#endif
