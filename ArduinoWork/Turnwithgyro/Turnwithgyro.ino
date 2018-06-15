#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);		
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double Angle;
MeGyro gyro;
void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
        	leftSpeed = speed;
        	rightSpeed = speed;
      }else if(direction == 2){
        	leftSpeed = -speed;
        	rightSpeed = -speed;
      }else if(direction == 3){
        	leftSpeed = -speed;
        	rightSpeed = speed;
      }else if(direction == 4){
        	leftSpeed = speed;
        	rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed)); //runs motor at leftspeed or - leftspeed
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed)); 
}
void turn(bool forward, int targetValue, int timeout, int cap, float KP, float KD){
  int dir;
  if(forward){dir = 3;}
  else{dir = 4;}
  int outTime = millis();
  int err = 0;
  int derr = 0;
  int err_sum = 0;
  int err_last = 0;
  int motorOutput;
  float KI = 0;
  float p;
  float i;
  float d;
  Angle = 0;
  while((outTime - millis() > timeout)){
    float currentValue = abs(gyro.getAngle(1));
    err = targetValue - currentValue;
    Serial.println(err);
    err_last = err;
    derr = err_last  - err;
    err_sum = err_sum + err;
    p = KP * err;
    d = d * derr;
    if(err<7){i = KI * err_sum;}
    motorOutput = p+i+d;
    if(motorOutput > cap){motorOutput = cap;}
    if(motorOutput < -cap){motorOutput = -cap;}

    move(dir, motorOutput);
    delay(50);
    
  }
  delay(15);
}



void setup(){
    gyro.begin();
    Angle = gyro.getAngle(1); //gets gyro from port 1
}

void loop(){
    turn(true, 90, 1000, 127, 4.5, 5);
    delay(1000);
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    gyro.update();   
}

