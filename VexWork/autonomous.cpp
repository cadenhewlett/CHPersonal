#include "main.h"
#include "lcd.h"
//#include "variables.h"


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous() {
  auto drive = ChassisControllerFactory::create(
    {1, 2}, // Left motors
    {-9, -10},   // Right motors
    AbstractMotor::gearset::green, // Torque gearset
    {3.25_in, 12.6_in} // 3.25 inch wheels, 12.5 inch wheelbase width
  );
  auto profileController = AsyncControllerFactory::motionProfile(
    1.0,  // Maximum linear velocity of the Chassis in m/s
    2.0,  // Maximum linear acceleration of the Chassis in m/s/s
    10.0, // Maximum linear jerk of the Chassis in m/s/s/s
    drive // Chassis Controller
  );
  okapi::Motor fly = 3_mtr;
  okapi::Motor InsideRoller = 6_mtr; //use rmtr for invert
  okapi::Motor Roller = 5_mtr;
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3.5_ft, 0_ft, 0_deg}},  "TEST");
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0_ft, 0_ft, -45_deg}}, "turn45");




if(currentAuto == 0){
 drive.turnAngle(90_deg);
}else if(currentAuto == 1){
   // AUTO 2 - blue
  //  isAuto = pros::competition::is_autonomous();
    profileController.setTarget("TEST");
    profileController.waitUntilSettled();
    Roller.move_voltage(-9000);
    InsideRoller.move_voltage(4000);
    pros::delay(1000);
    Roller.move_voltage(0);
    InsideRoller.move_voltage(0);
    drive.moveDistance(-1.5_ft);
    drive.waitUntilSettled();
    drive.turnAngle(-150_deg);
    drive.waitUntilSettled();
    Roller.moveVoltage(12000);
    drive.setMaxVelocity(350);
    drive.moveDistance(1.5_ft);
    drive.setMaxVelocity(127);
    Roller.moveVoltage(0);
    drive.waitUntilSettled();
    drive.setMaxVelocity(600);
    drive.moveDistance(-0.85_ft);
    drive.waitUntilSettled();
    drive.turnAngle(-150_deg);
    drive.waitUntilSettled();
    Roller.moveVoltage(-12000);
    drive.moveDistance(2.6_ft);
    Roller.moveVoltage(0);
    InsideRoller.moveVoltage(0);
    drive.turnAngle(-5_deg);
    drive.waitUntilSettled();

}else if(currentAuto == 3){
  // AUTO 1 - red 2caps platform

   profileController.setTarget("TEST");
   profileController.waitUntilSettled();
   drive.setMaxVelocity(600);
   Roller.move_voltage(-9000);
   InsideRoller.move_voltage(4000);
   pros::delay(1000);
   Roller.move_voltage(0);
   InsideRoller.move_voltage(0);
   //drive.moveDistance(-1.15_ft);
   //drive.waitUntilSettled();
   drive.turnAngle(55_deg);
   drive.waitUntilSettled();
   Roller.moveVoltage(12000);
   drive.setMaxVelocity(300);
   drive.moveDistance(2.4_ft);
   drive.setMaxVelocity(600);
   Roller.moveVoltage(0);
   drive.waitUntilSettled();
   drive.moveDistance(-1.2_ft);
   drive.waitUntilSettled();
   drive.turnAngle(225_deg);
   drive.waitUntilSettled();
   fly.move(0);
   Roller.moveVoltage(-12000);
   drive.moveDistance(2.8_ft);
   Roller.moveVoltage(0);
   InsideRoller.moveVoltage(0);
   drive.turnAngle(5_deg);
}
else{

}




  /*
  //Auto 3 - Blue - Untested
 fly.move(-127);
 pros::delay(4500);
 InsideRoller.move_voltage(4000);
 profileController.setTarget("TEST");
 profileController.waitUntilSettled();
 drive.moveDistance(-2_ft);
 drive.waitUntilSettled();
 drive.turnAngle(-19_deg);
 drive.waitUntilSettled();
 Roller.move(127);
 drive.moveDistance(1.5_ft);
 drive.waitUntilSettled();
 Roller.move(0);
 drive.moveDistance(-1.5_ft);
 drive.waitUntilSettled();
 drive.turnAngle(-22_deg);
 drive.waitUntilSettled();
 Roller.move(-127);
*/
 //drive.moveDistance(-1.2_ft);
 //drive.waitUntilSettled();
 //drive.turnAngle(-45);


  /*

  pros::delay(1000);
  InsideRoller.moveVoltage(6000);
  pros::delay(750);
  drive.moveDistance(3_ft);
  drive.waitUntilSettled();
  profileController.setTarget("return");
  profileController.waitUntilSettled();
  drive.moveDistance(3_ft);
  Roller.moveVoltage(-12000);
  pros::delay(500);*/

}
