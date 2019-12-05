#include "main.h"
#include "display.h"
#include "vision.h"
#include <string.h>

extern const lv_img_t test_detail;
extern const lv_img_t logo;

extern lv_obj_t*tabs;
extern lv_obj_t*auto_op_tab;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*test_tab;
extern lv_obj_t*motor_test_tab;
extern lv_obj_t*gyroGauge;
//extern lv_obj_t*sys_battery_meter;
extern lv_obj_t*frontLED;

bool fwd;
bool on;

/*** CREATE FUNCTIONS FOR OUR OBJECTS ***/
lv_res_t dropDown_action(lv_obj_t * list){
  currentTestMotor = lv_ddlist_get_selected(list); //Changes Global Variable of Test motor to the Index of the List.

  return LV_RES_OK; //return OK for complete execution
}

lv_res_t autoSelect_action(lv_obj_t * selector){
  currentAuto = lv_roller_get_selected(selector); /*Changes the current auto to be the list option index*/

  return LV_RES_OK; //return OK for complete execution
}

lv_res_t fb_switch_action(lv_obj_t*swtch){
  if(lv_sw_get_state(swtch) == SWITCH_FORWARD){
    fwd = true;
  }
  else{
    fwd = false;
  }
  return LV_RES_OK; //return OK for complete execution
}
lv_res_t oo_switch_action(lv_obj_t*swtch){
  if(lv_sw_get_state(swtch) == SWITCH_FORWARD){
    on = true;
  }
  else{
    on = false;
  }
  return LV_RES_OK;
}

lv_obj_t * tabs = lv_tabview_create(lv_scr_act(), NULL); //Declare tabview on default tab
lv_obj_t * auto_op_tab = lv_tabview_add_tab(tabs, "Enabled"); //Declare a tab
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Info"); //Declare a tab
lv_obj_t * motor_test_tab = lv_tabview_add_tab(tabs,"Test");

lv_obj_t * autoSelector;
lv_obj_t * frontLED; //Declare an LED for the Front Light Sensor
lv_obj_t * backLED; //Declare an LED for the Back Light Sensor
lv_obj_t * lftLED; //Declare an LED for the Flywheel Target Velocirt
lv_obj_t * fnlLED;
lv_obj_t * motorBar1;
lv_obj_t * motorLabel1;
lv_obj_t * motorBar2;
lv_obj_t * motorLabel2;
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;
lv_obj_t * symbol_label;
lv_obj_t * gyroGauge; //Declare a gauge for the gyro position
lv_obj_t * OnOffSwitch; //Declare our on/off switch for motor testing
lv_obj_t * directionSwitch; //Delcare our Forward/Backward switch for motor testing
lv_obj_t * motorSelect; //Declares our dropdown list for selecting which motor to test
lv_obj_t * gyroLabel;
lv_obj_t * visionObjectLabel;

void Display::create1010Image(void)
{
  LV_IMG_DECLARE(logoNew);//declare from our C file
  lv_obj_t * img2 = lv_img_create(auto_op_tab, NULL); //create the new image
  lv_img_set_src(img2, &logoNew);//sets the source of the image to be the array from the C File
  lv_obj_align(img2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0); //align the image
//  lv_obj_set_size(img2, 130, 170);
}

void Display::createOpLEDs(void)
{
    frontLED = lv_led_create(auto_op_tab, NULL); //Declare an LED for the Front Light Sensor
  	backLED = lv_led_create(auto_op_tab, NULL); //Declare an LED for the Back Light Sensor
  	lftLED = lv_led_create(auto_op_tab, NULL); //Declare an LED for the Flywheel Target Velocirt
  	fnlLED = lv_led_create(auto_op_tab, NULL);

  	lv_obj_align(frontLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40); //Align our topmost LED to the top right of the screen
  	lv_obj_align(backLED, frontLED, LV_ALIGN_CENTER, 0, 45); //Align our middle LED to the topmost LED and adjust the Y Value
  	lv_obj_align(lftLED, backLED, LV_ALIGN_CENTER, 0, 45); //Align the bottomost LED to the middle LED and adjust the Y Value for equal displacement
  	lv_obj_align(fnlLED, lftLED, LV_ALIGN_CENTER, 0, 45);

  	lv_obj_set_size(frontLED, 50, 35);
  	lv_obj_set_size(backLED, 50, 35);
  	lv_obj_set_size(lftLED, 50, 35);
  	lv_obj_set_size(fnlLED, 50, 35);

  	lv_obj_t * frontLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Front Light Sensor LED
  	lv_obj_t * backLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Back Light Sensor LED
  	lv_obj_t * fwLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Flywheel Target Velocity LED
  	lv_obj_t * fnlLabel = lv_label_create(auto_op_tab, NULL);

  	lv_obj_align(frontLabel, frontLED, LV_ALIGN_CENTER, 0, 0); //Align our frontLabel to the frontLED with an X adjustment of 60 units
  	lv_obj_align(backLabel, backLED, LV_ALIGN_CENTER, 0, 0); //Align our backLabel to the backLED with an X adjustment of 60 units
  	lv_obj_align(fwLabel, lftLED, LV_ALIGN_CENTER, 0, 0); //Align our fwLabel to the fwLED with an X adjustment of 60 units
  	lv_obj_align(fnlLabel, fnlLED, LV_ALIGN_CENTER, 0, 0);

  	lv_label_set_text(backLabel, "BTR"); //Set text of frontLabel to 'BLS', meaning Back Light Sensor
  	lv_label_set_text(fwLabel, "LFT"); //Set text of frontLabel to 'FW', meaning Flywheel
  	lv_label_set_text(frontLabel, "BTN"); //Set text of frontLabel to 'FLS', meaning Front Light Sensor
  	lv_label_set_text(fnlLabel, "VSN");
}

void Display::createTitle(void){
  visionObjectLabel = lv_label_create(disabled_tab, NULL);
  lv_obj_align(visionObjectLabel, NULL, LV_ALIGN_IN_LEFT_MID, -1, 0);
  lv_label_set_recolor(visionObjectLabel, true);
  lv_label_set_text(visionObjectLabel, "test");
}

void Display::createGauge()
{
  static lv_color_t needle_colors[] = {LV_COLOR_YELLOW}; //array for needle colours


  gyroGauge = lv_gauge_create(disabled_tab, NULL); //create a gauge for the angler position
  gyroLabel = lv_label_create(disabled_tab, gyroGauge);
  //lv_gauge_set_style(gyroGauge, &style);
  lv_gauge_set_scale(gyroGauge, 360, 18, 0); //Scale of 360 Degrees, with 18 Dashes and 9 Labels
  lv_gauge_set_range(gyroGauge,  -180, 180); //Range of 0-3600, the possible Gyro Values
  lv_gauge_set_critical_value(gyroGauge, 180); //Critical value of 2700, meaning the last quarter is full
  lv_gauge_set_needle_count(gyroGauge, 1, needle_colors); //Creates 1 Needle that is Red
  lv_obj_set_size(gyroGauge, 100, 100); //Sets the size to a 180x180 Circle
  lv_obj_align(gyroGauge, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50); //Align in Left Mid with an X Adjustment of 10
  lv_obj_align(gyroLabel, NULL, LV_ALIGN_IN_LEFT_MID, 20, 75);

  motorBar1 = lv_bar_create(disabled_tab, NULL);
  motorLabel1 = lv_label_create(motorBar1, NULL);
  lv_label_set_recolor(motorLabel1, true);

  lv_obj_set_size(motorBar1, 30, 155);
  lv_obj_align(motorBar1, gyroGauge, LV_ALIGN_OUT_TOP_LEFT, 110, 110);
  lv_bar_set_range(motorBar1, 0, 680);

  lv_obj_set_size(motorLabel1, 30, 70);
  lv_obj_align(motorLabel1, motorBar1, LV_ALIGN_CENTER, 2, 0);
  //lv_label_set_text(motorLabel1, "#0a0000 M1\n 100#");

  motorBar2 = lv_bar_create(disabled_tab, NULL);
  motorLabel2 = lv_label_create(motorBar2, NULL);
  lv_label_set_recolor(motorLabel2, true);

  lv_obj_set_size(motorBar2, 30, 155);
  lv_obj_align(motorBar2, motorBar1, LV_ALIGN_IN_TOP_LEFT, 50, 0);
  lv_bar_set_range(motorBar2, 0, 680);

  lv_obj_set_size(motorLabel2, 30, 70);
  lv_obj_align(motorLabel2, motorBar2, LV_ALIGN_CENTER, 5, 0);
}

void Display::createAutoSelector(void){
  autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "None\nUPBlue\nUPRed\nSkills\nOther\nMore"); //sets options to our character array
  lv_obj_set_width(autoSelector, 80); //sets the widtho of our list
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action); //Sets the action to our previously defined function
  lv_obj_align(autoSelector, sys_battery_meter, LV_ALIGN_CENTER, 150, -5); //Align object

}

void Display::createBatteryMeter(void){
  sys_battery_meter = lv_lmeter_create(disabled_tab, NULL);
  bat_meter_label = lv_label_create(sys_battery_meter, NULL);
  symbol_label =  lv_label_create(sys_battery_meter, NULL);
  lv_lmeter_set_range(sys_battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, 45, 10);
  lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, 8, -10);
  lv_obj_align(symbol_label, bat_meter_label, LV_ALIGN_CENTER, -10, 20);
  lv_lmeter_set_value(sys_battery_meter, 75);
  //lv_label_set_text(bat_meter_label, SYMBOL_BATTERY_2);
  lv_label_set_text(symbol_label, "Battery");
//lv_obj_align(bat_meter_label, sys_battery_meter, LV
}
void Display::createMotorTest(void){

  lv_obj_t*motorSelect = lv_ddlist_create(motor_test_tab, NULL); //declare dropdown list
  lv_obj_t*OnOffSwitch = lv_sw_create(motor_test_tab, NULL); //declare switches
  lv_obj_t*directionSwitch = lv_sw_create(motor_test_tab, NULL); //decoare direction switch
  lv_obj_t*OnOffLabel = lv_label_create(OnOffSwitch, NULL); //declare and create laabel
  lv_obj_t*directionLabel = lv_label_create(directionSwitch, NULL);//declare and create label

  lv_sw_set_action(OnOffSwitch, oo_switch_action); //sets the action of the switch to be previously defined function
  lv_sw_set_action(directionSwitch, fb_switch_action); //sets the action of the other switcch to be the other previously defined switch function

  lv_label_set_text(directionLabel, "<BCK : FWD>"); //sets label text
  lv_label_set_text(OnOffLabel, "<OFF : ON>"); //sets label text

  lv_obj_align(OnOffSwitch, NULL, LV_ALIGN_IN_TOP_RIGHT, -25, -25); //align switch to Top Right with XY change of -25, -25
  lv_obj_align(directionSwitch, NULL, LV_ALIGN_IN_TOP_RIGHT, -25, -50); //align switch to Top Right with XY change of -25, -50
  lv_obj_set_width(motorSelect, 120); //sets the width of our ddlist
  lv_obj_align(motorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 0 , -25); //align DropDown List in the Top Left with XY change of 0, -25
  lv_ddlist_set_options(motorSelect, "None\nBaseFL\nBaseFR\nBaseBL\nBaseBR\nLift1\nLift2\n"); //creates the options in the dropdown list. New optionsn are separated with the '\n'
  lv_ddlist_set_action(motorSelect, dropDown_action); //swts the action of the dropdown to be the previously defined function
  lv_ddlist_set_sb_mode(motorSelect, LV_SB_MODE_ON); //Sets the Scrollbar for the dropdown to be on
}

//TAB_TEST

void Display::motorTest(void)
{
  /*If the on switch is on, move the motor a direction multiplied by the forward switch
  moves the motor at index i, where i is the element selected from the drop down menu*/
  SystemMotors[currentTestMotor].move(
    (on ? 67 : 0 ) * (fwd ? 1 : -1)
  );

}

void Display::refresh(void) //refreshes values sent to the screen
{
//  lv_lmeter_set_value(sys_battery_meter, pros::battery::get_capacity()); //standin
  switch(lv_tabview_get_tab_act(tabs)){ //switch case statement that will only update values for active tab

    case TAB_DISPLAY: //Main Tab for Displaying Match info and Logo

      if(button.get_value() == HIGH){lv_led_on(frontLED);} //If the front light sensor reading is less than 2700, turn on the LED
      else{lv_led_off(frontLED);} //Otherwise it is off

  //    if((camera.getObjectXVal(ORN_CUBE) < 175) && camera.getObjectXVal(ORN_CUBE) > 125){lv_led_on(fnlLED);}
  //    else{lv_led_off(fnlLED);}

      if((abs(LiftR.get_position())) > 250){lv_led_on(lftLED);} //If the actualy flywheel velocity is greater than 550, turn on the LED
      else{lv_led_off(lftLED);} //Otherwise it is off

    //  if(TrayMotor.get_temperature() > 22){lv_led_on(backLED);} //If the back light sensor reading is less than 2700, turn on the LED
    //  else{lv_led_off(backLED);} //Otherwise it is off

    case TAB_INFO: //Information Tab with battery levels and other Information

      vision_object_s_t biggestObject = visionSensor.get_by_size(0);

    //  std::string colourMod = "#ffffff";
    if(biggestObject.signature == 1){
        lv_label_set_text(visionObjectLabel, ("#06d606 ""Green X:" + std::to_string(camera.getObjectXVal(biggestObject.signature))+" #" ).c_str()); //display colour and X Value of largest vision object
    }
    else if(biggestObject.signature == 2){
      lv_label_set_text(visionObjectLabel, ("#9705ff ""Purple X:" + std::to_string(camera.getObjectXVal(biggestObject.signature))+" #" ).c_str()); //display colour and X Value of largest vision object
    }
    else if(biggestObject.signature == 3){
        lv_label_set_text(visionObjectLabel, ("#fc5e03 ""Orange X:" + std::to_string(camera.getObjectXVal(biggestObject.signature))+" #" ).c_str()); //display colour and X Value of largest vision object
    }
    else{
      lv_label_set_text(visionObjectLabel, "No Object");
    }

      int baseOutput = abs(TrayMotor.get_position());
      int liftOutput = abs(LiftL.get_position());
      lv_bar_set_value(motorBar1, baseOutput);
      lv_bar_set_value(motorBar2, liftOutput);

      int level = pros::battery::get_capacity();
      lv_lmeter_set_value(sys_battery_meter, level);

      lv_label_set_text(motorLabel2, (std::to_string(abs(liftOutput)).c_str()));
      lv_label_set_text(motorLabel1, (std::to_string(baseOutput)).c_str());
/*
      if (liftOutput > 0) { lv_label_set_text(motorLabel2, ("#0a0000 " + std::to_string(liftOutput) + " #").c_str()); }
	    else { lv_label_set_text(motorLabel2, ("# CCC978 "  + std::to_string(liftOutput) + " #").c_str());}

      if (baseOutput > 0) { lv_label_set_text(motorLabel1, ("#0a0000 " + std::to_string(baseOutput) + " #").c_str()); }
      else { lv_label_set_text(motorLabel1, ("#CCC978"  + std::to_string(baseOutput) + " #").c_str());}
*/
      lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //convert level(int) to string to a const char
      lv_label_set_text(gyroLabel, (std::to_string((double)gyro.get_value()/10) + "°").c_str()); // convert gyro value to a 360 degree val, then conver string to a constant character and  output to the system
    //  lv_label_set_text(gyroLabel, (std::to_string(biggestObject.signature).c_str()));
      lv_gauge_set_value(gyroGauge, 0, (gyro.get_value() / 10)); //Sets our gauge position to be the gyro position

/*
+
   "Y: " + std::to_string(camera.getObjectYVal(largestObject)) + "\n" +
   "W: " +  std::to_string(camera.getObjectWidth(largestObject)) + "\n" +
   "H: " + std::to_string(camera.getObjectHeight(GRN_CUBE))
*/
  }
//  lv_lmeter_set_value(bat_meter_label, level);

  delay(20);
}

void Display::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE); //changes active tab
}

void Display::createScreen(void)
{

    lv_theme_t *th = lv_theme_alien_init(60, NULL); //Sets the theme, 60 For TTYellow
    lv_tabview_set_sliding(tabs, false); //do not slide the tabs to save brain powah
    lv_tabview_set_anim_time(tabs, 0); //Disable animations to save the brain

    //Call our functions
    createTitle();
    create1010Image();
    createBatteryMeter();
    createOpLEDs();
    createGauge();
    createAutoSelector();
    createMotorTest();
  //  createBackground();

}
