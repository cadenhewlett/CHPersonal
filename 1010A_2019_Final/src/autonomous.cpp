#include "main.h"
#include "functions.hpp"
#include "lcd.h"
using namespace okapi;
void autonomous() {
  Functions autoDrive; //creates a new instance of our functions class
  //auto angleController = okapi::AsyncControllerFactory::posIntegrated(AnglerPORT); //creates a new angle controller
  //double AngleTarget = angleController.getTarget(); //gets targetvalue of the angle controller
  //sensors
  auto startingPosition = angler.get_position(); //gets position of the angle controller
//  int pleaseWork = 20;
  capMax = 127;
 //see lcd.cpp for how the currentAuto is selected
    //RED CAPS
/*  angleController.setMaxVelocity(100);
  angleController.setTarget(startingPosition - 62);
  angleController.waitUntilSettled();
  delay(600);
  LinearLeft.move(127);
  LinearRight.move(127);
  delay(800);
  autoDrive.stopEverything();
  angleController.setTarget(startingPosition);
  autoDrive.turnValue(DIRECTION_RIGHT, 310, 1000, 0.8, 0.34237);
  autoDrive.stopDriving();
  Roller.move(127);
  autoDrive.driveValue(DIRECTION_FORWARD, 1150, 1100, 0.8, 0.7);
  autoDrive.stopDriving();
  delay(300);
  Roller.move(0);
  autoDrive.driveValue(DIRECTION_BACKWARD, 350, 850, 0.8, 0.7);
  autoDrive.stopEverything();
  Roller.move(-127);
  autoDrive.strafeValue(DIRECTION_RIGHT, 770, 1100, 0.8, 0.7);
  autoDrive.stopDriving();
  delay(100);
  autoDrive.driveValue(0.7, 645, 1000, 0.8, 0.7);
  autoDrive.stopEverything();
  autoDrive.driveValue(DIRECTION_BACKWARD, 352, 1000, 0.8, 0.7);
  autoDrive.stopEverything();
  autoDrive.turnValue(DIRECTION_LEFT, 450, 1000, 0.8, 0.7);
  autoDrive.stopEverything();
//  autoDrive.driveValue(DIRECTION_BACKWARD, 400, 1000, 0.8, 0.7);
  Roller.move(127);
  autoDrive.driveValue(1, 1950, 3000, 0.8, 0.7);
  autoDrive.stopDriving();
  autoDrive.turnValue(DIRECTION_RIGHT, 100, 750, 0.8, 0.7);
  //Roller.move(127);
*/


    //BLUE CAPS


//RED CAPS: KINDA WORKS
  //  capTarget = 300;
  //  delay(500);
/*
    LinearRight.move(-127);
    delay(400);
    Roller.move(-127);
    LinearRight.move(0);
    autoDrive.driveValue(DIRECTION_FORWARD, 935, 950, 0.8, 0.7); //935
    autoDrive.stopDriving();
    //autoDrive.smartIntake();
    delay(300);
    Roller.move(0);
    autoDrive.driveValue(DIRECTION_BACKWARD, 695, 800, 0.8, 0.7); //was 705
    autoDrive.stopDriving();
    delay(100);
    autoDrive.turnValue(DIRECTION_LEFT, 345, 750, 0.8, 0.7); //was 345 //was 325 //was 330
    autoDrive.stopDriving();
    angleTarget = 78; //was 85
    LinearRight.move(-127);
    delay(800);
    LinearRight.move(0);
    Roller.move(-127);
    delay(1100);
    Roller.move(0);
    angleTarget = 175;
    LinearRight.move(-127);

    delay(1200);
    LinearRight.move(0);
    angleTarget = 25; //was 20
    autoDrive.turnValue(DIRECTION_LEFT, 150, 500, 0.8, 0.7);//was 211
    autoDrive.stopDriving();
    capTarget = 20;
    autoDrive.driveValue(DIRECTION_BACKWARD, 622, 760, 0.8, 0.7);
    autoDrive.stopDriving();
    autoDrive.turnValue(DIRECTION_LEFT, 445, 850, 0.8, 0.7); //was 425 //worked at 435
    autoDrive.stopDriving();
    //autoDrive.strafeValue(DIRECTION_LEFT, 40, 450, 0.8, 0.7); //was 120
    capTarget = 10;
    autoDrive.driveValue(DIRECTION_BACKWARD, 935, 1100, 0.8, 0.7);
    autoDrive.stopDriving();
    delay(550);
    capTarget = 570;
    delay(500);
    autoDrive.strafeValue(DIRECTION_RIGHT, 120, 200, 0.8, 0.7);
    autoDrive.driveValue(DIRECTION_FORWARD, 700, 800, 0.8, 0.7); //was 750
    autoDrive.turnValue(DIRECTION_LEFT, 490, 750, 0.8, 0.7); //was 530
    autoDrive.stopDriving();
    delay(300);
    autoDrive.strafeValue(DIRECTION_RIGHT, 80, 200, 0.8, 0.7); //was 50 //was 70 and LEFT
    autoDrive.stopDriving();
    //autoDrive.driveValue(DIRECTION_FORWARD, 50, 175, 0.8, 0.7);
    capTarget = 885;
    delay(760);
    autoDrive.driveValue(DIRECTION_BACKWARD, 300, 500, 0.8, 0.7);
    capTarget = 0;
    autoDrive.strafeValue(DIRECTION_LEFT, 600, 750, 0.8, 0.7);
    autoDrive.turnValue(DIRECTION_RIGHT, 935, 1200, 0.8, 0.7); //was 940
    autoDrive.stopDriving();
    Roller.move(-127);
    autoDrive.driveValue(DIRECTION_FORWARD, 1100, 1500, 0.8, 0.7);
    autoDrive.stopDriving();
*/
    //autoDrive.fence(0.8, 0.9, 750);
    //autoDrive.stopEverything();

/*
    //BLUE CAPS: KINDA WORKS

    LinearRight.move(-127);
    delay(400);
    Roller.move(-127);
    LinearRight.move(0);
    autoDrive.driveValue(DIRECTION_FORWARD, 935, 950, 0.8, 0.7); //935
    autoDrive.stopDriving();
    //autoDrive.smartIntake();
    delay(300);
    Roller.move(0);
    autoDrive.driveValue(DIRECTION_BACKWARD, 695, 800, 0.8, 0.7); //was 705
    autoDrive.stopDriving();
    delay(100);
    autoDrive.turnValue(DIRECTION_RIGHT, 320, 950, 0.8, 0.7); //was 345 //was 325 //was 315
    autoDrive.stopDriving();
    angleTarget = 78; //was 85
    LinearRight.move(-127);
    delay(800);
    LinearRight.move(0);
    Roller.move(-127);
    delay(1100);
    Roller.move(0);
    angleTarget = 175;
    LinearRight.move(-127);

    delay(1200);
    LinearRight.move(0);
    angleTarget = 25; //was 20
    autoDrive.turnValue(DIRECTION_RIGHT, 160, 500, 0.8, 0.7);//was 211
    autoDrive.stopDriving();
    capTarget = 20;
    autoDrive.driveValue(DIRECTION_BACKWARD, 622, 760, 0.8, 0.7);
    autoDrive.stopDriving();
    autoDrive.turnValue(DIRECTION_RIGHT, 427, 1100, 0.8, 0.7); //was 425 //worked at 435
    autoDrive.stopDriving();
    //autoDrive.strafeValue(DIRECTION_LEFT, 40, 450, 0.8, 0.7); //was 120
    capTarget = 10;
    autoDrive.driveValue(DIRECTION_BACKWARD, 950, 1100, 0.8, 0.7); //was 935
    autoDrive.stopDriving();
    delay(550);
    capTarget = 570;
    delay(500);
    autoDrive.strafeValue(DIRECTION_LEFT, 120, 200, 0.8, 0.7);
    autoDrive.driveValue(DIRECTION_FORWARD, 700, 800, 0.8, 0.7); //was 750
    autoDrive.turnValue(DIRECTION_RIGHT, 490, 750, 0.8, 0.7); //was 530
    autoDrive.stopDriving();
    delay(300);
    autoDrive.strafeValue(DIRECTION_LEFT, 80, 200, 0.8, 0.7); //was 50 //was 70 and LEFT
    autoDrive.stopDriving();
    autoDrive.driveValue(DIRECTION_FORWARD, 50, 175, 0.8, 0.7);
    capTarget = 885;
    delay(760);
    autoDrive.driveValue(DIRECTION_BACKWARD, 300, 500, 0.8, 0.7);
    capTarget = 0;
    autoDrive.strafeValue(DIRECTION_RIGHT, 600, 750, 0.8, 0.7);
    autoDrive.turnValue(DIRECTION_LEFT, 875, 1200, 0.8, 0.7); //was 940
    autoDrive.stopDriving();
    Roller.move(-127);
    autoDrive.driveValue(DIRECTION_FORWARD, 1205, 1500, 0.8, 0.7);
    autoDrive.stopDriving();
*/
//SKILLS
/*
LinearRight.move(-127);
delay(400);
Roller.move(127);
LinearRight.move(0);
autoDrive.driveValue(DIRECTION_FORWARD, 935, 950, 0.8, 0.7); //935
autoDrive.stopDriving();
//autoDrive.smartIntake();
delay(300);
Roller.move(0);
autoDrive.driveValue(DIRECTION_BACKWARD, 665, 800, 0.8, 0.7); //was 705 //was 695
autoDrive.stopDriving();
delay(100);
autoDrive.turnValue(DIRECTION_LEFT, 365, 500, 0.8, 0.7); //was 345 //was 325 //was 330
autoDrive.stopDriving();
angleTarget = 85; //was 78
LinearRight.move(-127);
delay(800);
LinearRight.move(0);
Roller.move(-127);
delay(1100);
Roller.move(0);
angleTarget = 175;
LinearRight.move(-127);

delay(1200);
LinearRight.move(0);
angleTarget = 25; //was 20
autoDrive.turnValue(DIRECTION_LEFT, 150, 500, 0.8, 0.7);//was 211
autoDrive.stopDriving();
capTarget = 20;
autoDrive.driveValue(DIRECTION_BACKWARD, 622, 760, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.turnValue(DIRECTION_LEFT, 445, 1100, 0.8, 0.7); //was 425 //worked at 435
autoDrive.stopDriving();
//autoDrive.strafeValue(DIRECTION_LEFT, 40, 450, 0.8, 0.7); //was 120
capTarget = 10;
autoDrive.driveValue(DIRECTION_BACKWARD, 935, 1100, 0.8, 0.7);
autoDrive.stopDriving();
delay(550);
capTarget = 570;
delay(500);
autoDrive.strafeValue(DIRECTION_RIGHT, 120, 200, 0.8, 0.7);
autoDrive.driveValue(DIRECTION_FORWARD, 700, 800, 0.8, 0.7); //was 750
autoDrive.turnValue(DIRECTION_LEFT, 490, 750, 0.8, 0.7); //was 530
autoDrive.stopDriving();
delay(300);
autoDrive.strafeValue(DIRECTION_RIGHT, 80, 200, 0.8, 0.7); //was 50 //was 70 and LEFT
autoDrive.stopDriving();
autoDrive.driveValue(DIRECTION_FORWARD, 50, 175, 0.8, 0.7);
capTarget = 885;
delay(760);
autoDrive.driveValue(DIRECTION_BACKWARD, 300, 500, 0.8, 0.7);
capTarget = 0;
autoDrive.strafeValue(DIRECTION_LEFT, 600, 750, 0.8, 0.7);
autoDrive.turnValue(DIRECTION_RIGHT, 920, 1200, 0.8, 0.7); //was 940
autoDrive.stopDriving();
Roller.move(-127);
autoDrive.driveValue(DIRECTION_FORWARD, 1110, 1500, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.turnValue(DIRECTION_RIGHT, 480, 800, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.driveValue(DIRECTION_FORWARD, 900, 1500, 0.8, 0.7);
*/
//autoDrive.fence(0.8, 0.9, 750);
//autoDrive.stopEverything();

//  BLUE COUNTER FAR
//delay(400);

LinearRight.move(-127);
Roller.move(-127);
delay(400);
//LinearRight.move(0);
LinearRight.move(0);
capTarget = 0;
autoDrive.driveValue(DIRECTION_FORWARD, 935, 950, 0.8, 0.7); //935
delay(250);
Roller.move(0);
autoDrive.driveValue(DIRECTION_BACKWARD, 200, 760, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.turnValue(DIRECTION_RIGHT, 257, 1100, 0.8, 0.7); //was 425 //worked at 435 //was 255
delay(100);
//autoDrive.turnValue(DIRECTION_RIGHT, 315, 750, 0.8, 0.7); //was 345 //was 325 //was 330
autoDrive.stopDriving();
angleTarget = 50; //was 50 //was 35
delay(4000);
LinearRight.move(-127);
delay(900);
LinearRight.move(0);
Roller.move(-127);
delay(1100);
Roller.move(0);
angleTarget = 135; //was 96
LinearRight.move(-127);
delay(1500);
LinearRight.move(0);
autoDrive.turnValue(DIRECTION_LEFT, 687, 1100, 0.8, 0.7); //was135
autoDrive.stopDriving();
autoDrive.strafeValue(DIRECTION_RIGHT, 635, 1100, 0.8, 0.7);
autoDrive.stopDriving();
delay(350);
//capTarget = 40;
Roller.move(127);
autoDrive.driveValue(DIRECTION_FORWARD, 725, 1000, 0.8, 0.7);
delay(350);
autoDrive.stopDriving();
autoDrive.driveValue(DIRECTION_BACKWARD, 350, 750, 0.8, 0.7);
//capTarget = 570;
//delay(500);
/*autoDrive.driveValue(DIRECTION_FORWARD, 250, 300, 0.8, 0.7);
autoDrive.strafeValue(DIRECTION_RIGHT, 750, 1000, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.driveValue(DIRECTION_BACKWARD, 375, 300, 0.8, 0.7);

autoDrive.stopDriving();
delay(650);
capTarget = 885;
autoDrive.driveValue(DIRECTION_BACKWARD, 200, 300, 0.8, 0.7);
*/
capTarget = 0;
autoDrive.stopDriving();


//RED COUNTER far
/*
LinearRight.move(-127);
Roller.move(-127);
delay(400);
//LinearRight.move(0);
LinearRight.move(0);
capTarget = 0;
autoDrive.driveValue(DIRECTION_FORWARD, 935, 950, 0.8, 0.7); //935
delay(250);
Roller.move(0);
autoDrive.driveValue(DIRECTION_BACKWARD, 200, 760, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.turnValue(DIRECTION_LEFT, 265, 1100, 0.8, 0.7); //was 425 //worked at 435 //was 255
delay(100);
//autoDrive.turnValue(DIRECTION_RIGHT, 315, 750, 0.8, 0.7); //was 345 //was 325 //was 330
autoDrive.stopDriving();
angleTarget = 50; //was 50 //was 35
delay(3000);
LinearRight.move(-127);
delay(800);
LinearRight.move(0);
Roller.move(-127);
delay(1100);
Roller.move(0);
angleTarget = 125; //was 96
LinearRight.move(-127);
delay(1500);
LinearRight.move(0);
//utoDrive.turnValue(DIRECTION_LEFT, 145, 1100, 0.8, 0.7); //was135
autoDrive.turnValue(DIRECTION_RIGHT, 695, 1000, 0.8, 0.7);
autoDrive.stopDriving();
//autoDrive.strafeValue(DIRECTION_RIGHT, 635, 1100, 0.8, 0.7);
autoDrive.strafeValue(DIRECTION_LEFT, 635, 1100, 0.8, 0.7);
autoDrive.stopDriving();
delay(350);
//capTarget = 40;
Roller.move(127);
autoDrive.driveValue(DIRECTION_FORWARD, 555, 1000, 0.8, 0.7);
delay(350);
Roller.move(0);
autoDrive.stopDriving();
//capTarget = 570;
delay(500);
autoDrive.driveValue(DIRECTION_BACKWARD, 350, 1000, 0.8, 0.7);
capTarget = 0;
autoDrive.stopDriving();
*/
//autoDrive.driveValue(DIRECTION_FORWARD, 250, 300, 0.8, 0.7);
/*autoDrive.strafeValue(DIRECTION_LEFT, 850, 1000, 0.8, 0.7);
autoDrive.stopDriving();
autoDrive.driveValue(DIRECTION_BACKWARD, 375, 300, 0.8, 0.7);
autoDrive.stopDriving();
delay(650);
//capTarget = 885;
autoDrive.driveValue(DIRECTION_BACKWARD, 200, 300, 0.8, 0.7);
*/



  /*  autoDrive.driveValue(DIRECTION_BACKWARD, 350, 850, 0.8, 0.7);

    Roller.move(-127);
    autoDrive.strafeValue(DIRECTION_LEFT, 770, 1100, 0.8, 0.7);
    //autoDrive.stopEverything();
    delay(100);
    //Roller.move(-127);
    autoDrive.driveValue(0.7, 620, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    autoDrive.driveValue(DIRECTION_BACKWARD, 320, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    autoDrive.turnValue(DIRECTION_RIGHT, 405, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    Roller.move(127);
  //  autoDrive.driveValue(DIRECTION_BACKWARD, 400, 1000, 0.8, 0.7);
      autoDrive.driveValue(DIRECTION_FORWARD, 1900, 3000, 0.8, 0.7);
    autoDrive.stopDriving(); */
//    autoDrive.turnValue(DIRECTION_LEFT, 100, 750, 0.8, 0.7);
    // Roller.move(127);
  /*}
  else if(currentAuto == 4){


  }
  else if(currentAuto == 5){
    //Skills
    angleController.setMaxVelocity(300);
    angleController.setTarget(startingPosition - 62);
    angleController.waitUntilSettled();
    delay(600);
    LinearLeft.move(127);
    LinearRight.move(127);
    delay(800);
    autoDrive.stopEverything();
    angleController.setTarget(startingPosition);
    autoDrive.turnValue(DIRECTION_LEFT, 315, 1000, 0.8, 0.7);
    autoDrive.stopDriving();
    Roller.move(-127);
    autoDrive.driveValue(DIRECTION_FORWARD, 1150, 1100, 0.8, 0.7);
    autoDrive.stopDriving();
    delay(300);
    Roller.move(0);
    autoDrive.driveValue(DIRECTION_BACKWARD, 270, 850, 0.8, 0.7);
    autoDrive.stopEverything();
    autoDrive.strafeValue(DIRECTION_LEFT, 700, 1100, 0.8, 0.7);
    autoDrive.stopEverything();
    delay(100);
    Roller.move(-127);
    autoDrive.driveValue(0.5, 620, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    autoDrive.driveValue(DIRECTION_BACKWARD, 225, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    autoDrive.turnValue(DIRECTION_RIGHT, 470, 1000, 0.8, 0.7);
    autoDrive.stopEverything();
    Roller.move(127);
  //  autoDrive.driveValue(DIRECTION_BACKWARD, 400, 1000, 0.8, 0.7);
    autoDrive.driveValue(1, 1950, 3000, 0.8, 0.7);
    autoDrive.stopDriving();
    autoDrive.turnValue(DIRECTION_LEFT, 100, 750, 0.8, 0.7);
    // Roller.move(127);

  }*/
}
