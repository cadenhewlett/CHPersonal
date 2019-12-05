#include "main.h"

void autonomous() {
  screen.setActiveTab(TAB_DISPLAY);
  screen.refresh();
//  DR4B.autoLift(450, 5000, false);
//  DR4B.autoAngler(250, 1200);

//  DR4B.autoLift(presets[1], 560, true);

//  TrayMotor.move(-10);
  DR4B.autoLift(305, 470, false);
  delay(500);
//  intake.autoIntake(127);
  DR4B.autoLift(presets[0], 350, false);
  delay(450);
//  DR4B.autoAngler(520, 5000);

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

  intake.autoIntake(127);
  base.MoveDistance(DIRECTION_FORWARD, 1050, 1500, 80);
  base.stopDriving();
  delay(750);
  intake.autoIntake(0);
  base.MoveDistance(DIRECTION_BACKWARD, 870, 1150, 90);
//  base.driveOnAngle( (M_PI/3.86), QUADRANT_3, 2000, 2600);
  base.stopDriving();
  delay(200);
  intake.autoIntake(67);
  base.StrafeDistance(DIRECTION_LEFT, 1050, 1250);
  delay(150);
  intake.autoIntake(127);
  base.MoveDistance(DIRECTION_FORWARD, 1000, 1500, 80);
  base.stopDriving();
  delay(400);
  intake.autoIntake(67);
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
  intake.autoIntake(0);
  base.stopDriving();
  delay(450);
  DR4B.autoAngler(525, 1350);
  delay(150);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 750, 127);
  base.stopDriving();
  delay(200);
  DR4B.autoAngler(0, 750);

}
else if(currentAuto == AUTO_UNPROTEC_RED){

  intake.autoIntake(127);
  base.MoveDistance(DIRECTION_FORWARD, 1050, 1500, 80);
  base.stopDriving();
  delay(300);
  intake.autoIntake(0);
  base.MoveDistance(DIRECTION_BACKWARD, 900, 1150, 100);

//  base.driveOnAngle( (M_PI/3.86), QUADRANT_3, 2000, 2600);
  base.stopDriving();
  delay(100);
  intake.autoIntake(30);
  base.StrafeDistance(DIRECTION_RIGHT, 1050, 1250);
  delay(150);
  intake.autoIntake(127);
  base.MoveDistance(DIRECTION_FORWARD, 1000, 1500, 80);
  base.stopDriving();
  delay(300);
  intake.autoIntake(67);
  base.MoveDistance(DIRECTION_BACKWARD, 800, 900, 127);
  base.stopDriving();
  delay(150);
  base.TurnDistance(DIRECTION_RIGHT, 550, 700);
  intake.autoIntake(0);
  base.stopDriving();
  delay(100);
  base.StrafeDistance(DIRECTION_RIGHT, 750, 900);
  base.stopDriving();
  delay(100);
  base.MoveDistance(DIRECTION_FORWARD, 335, 750, 80);
  base.stopDriving();
  delay(450);
  DR4B.autoAngler(525, 1250);
  delay(650);
  base.MoveDistance(DIRECTION_BACKWARD, 450, 750, 127);
  base.stopDriving();
  delay(200);
  DR4B.autoAngler(0, 750);
}
else if (currentAuto == AUTO_SKILLS){
  intake.autoIntake(127);
  base.MoveDistance(DIRECTION_FORWARD, 975, 1500, 80);
  base.stopDriving();
  delay(300);
  base.StrafeDistance(DIRECTION_RIGHT, 350, 800);
  base.stopDriving();
  delay(500);
  base.MoveDistance(DIRECTION_FORWARD, 250, 800, 80);
  base.stopDriving();
  delay(500);
  intake.autoIntake(0);
  DR4B.autoLift(500, 900, true);
  base.MoveDistance(DIRECTION_FORWARD, 70, 250, 80);
  base.stopDriving();
  intake.autoIntake(-127);
}
}
