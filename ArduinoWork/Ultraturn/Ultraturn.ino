#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);		
MeGyro gyro;
MeUltrasonicSensor ultrasonic_3(3);
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
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
				
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
double distance;
double Angle;
int kmarx;


void setup(){
    gyro.begin();
    Angle = gyro.getAngle(1); //gets gyro from port 1
    distance = ultrasonic_3.distanceCm();
    Serial.begin(9600);
    while(!Serial){}
    Serial.println("Ultrasonic and/or Turn Test");
    Serial.println("Enter a number and hit enter");
    Serial.println("Please Enter Test Type");
    Serial.println("1. Ultrasonic Value Test");
    Serial.println("2. Gyroscope Value Test");
    Serial.println("3. PID Test (Send Values)");
    Serial.println("4. Ultrasonic Stop Test");
    Serial.println("5. Ultrasonic Turn Test (with PID)");
    int entered = Serial.read();
    if(entered == '/n'){
      Serial.print("[2J"); 
      int selected = Serial.read();
      if(!(isDigit(selected))){
        Serial.print("[2J"); 
        Serial.println("Invalid Entry");
      }
      else{
        Serial.print("[2J"); 
        if(selected < 6){
          Serial.println("You have selected");
          Serial.print(selected);
          kmarx = selected;
          Serial.println("Enter OK to continue...");
        }
      }
   
    }
}

void turn(bool forward, bool sendValues, int targetValue, int timeout, int cap, float KP, float KD){
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
    if(sendValues){Serial.println(err);}
    else{}
    err = targetValue - currentValue;
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
void loop(){
    if(Serial.read() == 'OK'){
      switch(kmarx){
        case 1:
          Serial.println(distance);
          delay(100);
          break;
        case 2:
          Serial.println(Angle);
          delay(100);
          break;
        case 3:
          turn(true, true, 90, 1000, 127, 4.5, 5);
          break;
        default:
          Serial.println("this is the default");
          break;
        
      }
      }
      _loop();
    }
    



void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)
    _loop();
}


void _loop(){
    gyro.update();
    //ultrasonic_3.update();
}

