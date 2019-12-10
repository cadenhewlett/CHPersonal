#include "main.h"

int armAutoTarget = 0;
int anglerAutoTarget = 0;

void autonomous() {

  screen.setActiveTab(TAB_DISPLAY);
  screen.refresh();
//  DR4B.autoLift(450, 5000, false);
//  DR4B.autoAngler(250, 1200);

//  DR4B.autoLift(presets[1], 560, true);
/*
DR4B.autoAngler(presets[0], 850);
delay(560);
*/
//  TrayMotor.move(-10);
//    DR4B.autoLift(500, 900, true);

  armAutoTarget = presets[1];
  delay(500);
//  intake.autoIntake(127);
  armAutoTarget = presets[0];
  delay(650);

/*
  DR4B.autoAngler(870, 1600);
  delay(1000);
*/
  //DR4B.autoAngler(presets[0], 900);
//  DR4B.autoAngler(520, 5000);

//base.fence(0.55, 0.8, 6000);
//  DR4B.autoLift(400, 1750, true);
if(currentAuto == NO_AUTO_SELECTED){
    //camera.centerToObject(ORN_CUBE, 130, 40000);
/*
    base.MoveDistance(DIRECTION_FORWARD, 540, 800);
    base.stopDriving();
    delay(500);
    base.TurnDistance(DIRECTION_RIGHT, 325, 900);
    delay(200);
    base.stopDriving();
    base.MoveDistance(DIRECTION_FORWARD, 650, 1000);
    delay(200);
    base.stopDriving();
    intake.autoIntake(1000, 330);
    delay(200);
    base.MoveDistance(DIRECTION_BACKWARD, 450, 800);
    base.stopDriving();

    intake.autoIntake(1000, 0);
*/
  /*
    base.MoveDistance(DIRECTION_FORWARD, 300, 750);
    base.stopDriving();
    delay(200);
    base.TurnDistance(DIRECTION_LEFT, 350, 1200);
    delay(200);
    base.stopDriving();
    intake.autoIntake(500, 330);
    base.MoveDistance(DIRECTION_FORWARD, 500, 750);
    base.stopDriving();
    intake.autoIntake(500, 0);
    delay(250);
    base.MoveDistance(DIRECTION_BACKWARD, 550, 750);
    base.stopDriving();
    base.TurnDistance(DIRECTION_LEFT, 350, 1200);
    base.stopDriving();
    base.MoveDistance(DIRECTION_FORWARD, 400, 750);
    base.stopDriving();
    intake.autoIntake(500, 330);
    delay(150);
    base.MoveDistance(DIRECTION_BACKWARD, 200, 750);
    */

  }/*
  else if(currentAuto == RED_FRONT){
    //test
    base.MoveDistance(DIRECTION_FORWARD, 400, 1000);
    delay(250);
    base.stopDriving();
    DR4B.autoLift(700, 3);
    delay(250);
    DR4B.autoLift(700, 5);
    base.TurnDistance(DIRECTION_RIGHT, 400, 700);
    delay(250);
    base.stopDriving();
  }
*/

else if(currentAuto == AUTO_UNPROTEC_BLUE){

  rollerSpeed = 127;
  base.MoveDistance(DIRECTION_FORWARD, 1050, 1500, 80);
  base.stopDriving();
  delay(750);
  rollerSpeed = 0;
  base.MoveDistance(DIRECTION_BACKWARD, 870, 1150, 90);
//  base.driveOnAngle( (M_PI/3.86), QUADRANT_3, 2000, 2600);
  base.stopDriving();
  delay(200);
  rollerSpeed = 67;
  base.StrafeDistance(DIRECTION_LEFT, 1050, 1250);
  delay(150);
  rollerSpeed = 127;
  base.MoveDistance(DIRECTION_FORWARD, 1000, 1500, 80);
  base.stopDriving();
  delay(400);
  rollerSpeed = 67;
  base.MoveDistance(DIRECTION_BACKWARD, 800, 950, 127);
  base.stopDriving();
  delay(150);
  base.TurnDistance(DIRECTION_LEFT, 550, 700);
  base.stopDriving();
  delay(100);
  base.StrafeDistance(DIRECTION_LEFT, 750, 900);
  base.stopDriving();
  delay(100);
  base.MoveDistance(DIRECTION_FORWARD, 225, 720, 80);
  rollerSpeed = 0;
  base.stopDriving();
  delay(450);
  anglerAutoTarget = 870;
  delay(150);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 750, 127);
  base.stopDriving();
  delay(200);
  anglerAutoTarget = 0;

}
else if(currentAuto == AUTO_UNPROTEC_RED){

  rollerSpeed = 127;
  base.MoveDistance(DIRECTION_FORWARD, 1050, 1500, 80);
  base.stopDriving();
  delay(300);
  rollerSpeed = 0;
  base.MoveDistance(DIRECTION_BACKWARD, 900, 1150, 100);

//  base.driveOnAngle( (M_PI/3.86), QUADRANT_3, 2000, 2600);
  base.stopDriving();
  delay(100);
  rollerSpeed = 0;
  base.StrafeDistance(DIRECTION_RIGHT, 1050, 1250);
  delay(150);
  rollerSpeed = 127;
  base.MoveDistance(DIRECTION_FORWARD, 1000, 1500, 80);
  base.stopDriving();
  delay(300);
  rollerSpeed = 67;
  base.MoveDistance(DIRECTION_BACKWARD, 800, 900, 127);
  base.stopDriving();
  delay(150);
  base.TurnDistance(DIRECTION_RIGHT, 550, 700);
  rollerSpeed = 0;
  base.stopDriving();
  delay(100);
  base.StrafeDistance(DIRECTION_RIGHT, 750, 900);
  base.stopDriving();
  delay(100);
  base.MoveDistance(DIRECTION_FORWARD, 335, 750, 80);
  base.stopDriving();
  delay(450);
  anglerAutoTarget = 870;
  delay(650);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 750, 127);
  base.stopDriving();
  delay(200);
  anglerAutoTarget = 0;
}
else if (currentAuto == AUTO_SKILLS){
  rollerSpeed = 127;
  base.MoveDistance(DIRECTION_FORWARD, 1040, 1500, 80);
  base.stopDriving();
  delay(600);
  base.StrafeDistance(DIRECTION_RIGHT, 350, 800);
  base.stopDriving();
  delay(500);
  base.MoveDistance(DIRECTION_FORWARD, 250, 800, 80);
  base.stopDriving();
  delay(500);
  rollerSpeed = 0;
  base.MoveDistance(DIRECTION_BACKWARD, 75, 600, 80);
  armAutoTarget = CUBE_LIFT_PRESET;
  delay(500);
  base.MoveDistance(DIRECTION_FORWARD, 120, 350, 80);
  base.stopDriving();
  delay(250);
  rollerSpeed = -127;
  delay(650);
  rollerSpeed = 0;
  base.MoveDistance(DIRECTION_BACKWARD, 450, 800, 80);
  armAutoTarget = presets[0];
  rollerSpeed = 0;
  delay(350);
  base.stopDriving();
  base.TurnDistance(DIRECTION_LEFT, 500, 850);
  delay(350);
  base.stopDriving();
  base.MoveDistance(DIRECTION_FORWARD, 330, 700, 80);
  base.stopDriving();
  delay(500);
//  base.MoveDistance(DIRECTION_BACKWARD, 75, 600, 80);
  armAutoTarget = CUBE_LIFT_PRESET;
  delay(500);
  base.stopDriving();
  base.MoveDistance(DIRECTION_FORWARD, 150, 350, 50);
  base.stopDriving();
   delay(250);
  rollerSpeed = -90;
  delay(700);
  rollerSpeed = 0;
  base.MoveDistance(DIRECTION_BACKWARD, 185, 800, 80);
  base.stopDriving();
  delay(500);
  base.TurnDistance(DIRECTION_RIGHT, 525, 850);
  armAutoTarget = presets[0];
  base.stopDriving();
  rollerSpeed = 127;
  delay(500);
  base.MoveDistance(DIRECTION_FORWARD, 1275, 800, 80);
  base.stopDriving();
  delay(350);
  base.TurnDistance(DIRECTION_RIGHT, 50, 350);
  base.stopDriving();
  delay(350);
//This is a more reliable version that just scores a tower.
  base.MoveDistance(DIRECTION_FORWARD, 2600, 3700, 60);
  base.stopDriving();
  delay(2750);
  base.TurnDistance(DIRECTION_LEFT, 555, 1250); //was 545
  delay(350);
  base.StrafeDistance(DIRECTION_RIGHT, 1300, 1750);
  base.stopDriving();
/*
//This part goes for the third tower. It is removed for now.
  base.MoveDistance(DIRECTION_FORWARD, 2200, 2400, 80);
  base.stopDriving();
  delay(1050);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 800, 80);
  base.stopDriving();
  base.TurnDistance(DIRECTION_LEFT, 555, 1250); //was 545
  delay(350);
//  base.stopDriving();
//  base.StrafeDistance(DIRECTION_RIGHT, 400, 800);
  base.stopDriving();
  //base.MoveDistance(DIRECTION_FORWARD, 110, 550, 80);

  //COULD GO SIDEWAYS INTO VERTICAL PART OF WALL
  DR4B.autoLift(500, 900, true);
  delay(300);
  base.MoveDistance(DIRECTION_FORWARD, 250, 650, 80);
  base.stopDriving();
  intake.autoIntake(-90);
  delay(700);
  intake.autoIntake(0);
  base.MoveDistance(DIRECTION_BACKWARD, 350, 950, 80);
  DR4B.autoLift(presets[0], 900, false);
  delay(250);
  intake.autoIntake(127);
  base.TurnDistance(DIRECTION_LEFT, 560, 1150);
  base.stopDriving();
  delay(550);
  base.fence(0.55, 0.8, 1400);
  base.stopDriving();
  delay(550);
  base.TurnDistance(DIRECTION_RIGHT, 520, 950);
  base.stopDriving();
  base.StrafeDistance(DIRECTION_RIGHT, 300, 750);
  base.stopDriving();
*/
  delay(450);
  base.MoveDistance(DIRECTION_FORWARD, 580, 750, 67);
  base.stopDriving();
  rollerSpeed = 0;
  delay(450);
  anglerAutoTarget =  870;
  delay(550);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 750, 127);
  base.stopDriving();
  delay(200);
  anglerAutoTarget = 0;
  }
}
