#include "main.h"
#include "display.h"
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

lv_res_t dropDown_action(lv_obj_t * list){
  currentTestMotor = lv_ddlist_get_selected(list);

  return LV_RES_OK;
}

lv_res_t autoSelect_action(lv_obj_t * selector){
  currentAuto = lv_roller_get_selected(selector); /*Changes the current auto to be the list option index*/

  return LV_RES_OK;
}

lv_res_t fb_switch_action(lv_obj_t*swtch){
  if(lv_sw_get_state(swtch) == SWITCH_FORWARD){
    fwd = true;
  }
  else{
    fwd = false;
  }
  return LV_RES_OK;
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
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Disabled"); //Declare a tab
lv_obj_t * motor_test_tab = lv_tabview_add_tab(tabs,"Test");

lv_obj_t * frontLED; //Declare an LED for the Front Light Sensor
lv_obj_t * backLED; //Declare an LED for the Back Light Sensor
lv_obj_t * fwLED; //Declare an LED for the Flywheel Target Velocirt
lv_obj_t * sys_battery_meter;
lv_obj_t * bat_meter_label;
lv_obj_t * symbol_label;
lv_obj_t * gyroGauge; //Declare a gauge for the gyro position
lv_obj_t * OnOffSwitch; //Declare our on/off switch for motor testing
lv_obj_t * directionSwitch; //Delcare our Forward/Backward switch for motor testing
lv_obj_t * motorSelect; //Declares our dropdown list for selecting which motor to test
lv_obj_t * gyroLabel;
void Display::create1010Image(void)
{
  LV_IMG_DECLARE(logoNew);//declare from our C file
  lv_obj_t * img2 = lv_img_create(auto_op_tab, NULL); //create the new image
  lv_img_set_src(img2, &logoNew);//sets the source of the image to be the array from the C File
  lv_obj_align(img2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 0); //align the image
//  lv_obj_set_size(img2, 130, 170);
}

void Display::createTitle(void)
{
  lv_obj_t * title =  lv_label_create(disabled_tab, NULL); //Create a Label on the currently active screen
  lv_label_set_text(title, "Ten Ton Robotics - TEST"  );//Sets the text of the label
  lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 5); //Align object
}

void Display::createOpLEDs(void)
{
  frontLED = lv_led_create(auto_op_tab, NULL); //Create an LED for the Front Light Sensor on the Auto/Op tab
  backLED = lv_led_create(auto_op_tab, NULL); //Create an LED for the Back Light Sensor on the Auto/Op tab
  fwLED = lv_led_create(auto_op_tab, NULL); //Create an LED for the Flywheel Target Velocity on the Auto/Op tab
  lv_obj_t * frontLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Front Light Sensor LED
  lv_obj_t * backLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Back Light Sensor LED
  lv_obj_t * fwLabel = lv_label_create(auto_op_tab, NULL); //Create a Label for the Flywheel Target Velocity LED
  lv_obj_align(frontLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -63, 68); //Align our topmost LED to the top right of the screen
  lv_obj_align(backLED, frontLED, LV_ALIGN_CENTER, 0, 55); //Align our middle LED to the topmost LED and adjust the Y Value
  lv_obj_align(fwLED, backLED, LV_ALIGN_CENTER, 0, 55); //Align the bottomost LED to the middle LED and adjust the Y Value for equal displacement
  lv_obj_align(frontLabel, frontLED, LV_ALIGN_CENTER, 60, 0); //Align our frontLabel to the frontLED with an X adjustment of 60 units
  lv_obj_align(backLabel, backLED, LV_ALIGN_CENTER, 60, 0); //Align our backLabel to the backLED with an X adjustment of 60 units
  lv_obj_align(fwLabel, fwLED, LV_ALIGN_CENTER, 60, 0); //Align our fwLabel to the fwLED with an X adjustment of 60 units
  lv_label_set_text(backLabel, "BLS"); //Set text of frontLabel to 'BLS', meaning Back Light Sensor
  lv_label_set_text(fwLabel, "FW"); //Set text of frontLabel to 'FW', meaning Flywheel
  lv_label_set_text(frontLabel, "FLS"); //Set text of frontLabel to 'FLS', meaning Front Light Sensor
  lv_led_off(frontLED); //Sets default state to off
  lv_led_off(backLED); //Sets default state to off
  lv_led_off(fwLED); //Sets default state to off
}

void Display::createGauge()
{
  static lv_color_t needle_colors[] = {LV_COLOR_RED}; //array for needle colours

  /*Create a gauge*/
  gyroGauge = lv_gauge_create(disabled_tab, NULL); //create a gauge for the angler position
  gyroLabel = lv_label_create(disabled_tab, gyroGauge);
  //lv_gauge_set_style(gyroGauge, &style);
  lv_gauge_set_scale(gyroGauge, 360, 18, 9); //Scale of 360 Degrees, with 18 Dashes and 9 Labels
//  lv_gauge_set_range(gyroGauge,  0, 3600); //Range of 0-3600, the possible Gyro Values
  lv_gauge_set_critical_value(gyroGauge, 2700); //Critical value of 2700, meaning the last quarter is full
  lv_gauge_set_needle_count(gyroGauge, 1, needle_colors); //Creates 1 Needle that is Red
  lv_obj_set_size(gyroGauge, 80, 80); //Sets the size to a 180x180 Circle
  lv_obj_align(gyroGauge, sys_battery_meter, LV_ALIGN_IN_TOP_LEFT, -180, 0); //Align in Left Mid with an X Adjustment of 10
}

void Display::createAutoSelector(void){
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "Red\nBlue\nRed Front\nSkills\nOther\nMore"); //sets options to our character array
  lv_obj_set_width(autoSelector, 80); //sets the widtho of our list
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action); //Sets the action to our previously defined function
  lv_obj_align(autoSelector, sys_battery_meter, LV_ALIGN_CENTER, 150, -5); //Align object
}

void Display::createBackground(void){
  static lv_style_t style_bg;
  lv_style_copy(&style_bg, &lv_style_pretty);
  style_bg.body.main_color = LV_COLOR_MAKE(0xf5, 0x45, 0x2e);
  style_bg.body.grad_color = LV_COLOR_MAKE(0xb9, 0x1d, 0x09);
  style_bg.body.border.color = LV_COLOR_MAKE(0x3f, 0x0a, 0x03);
  style_bg.text.color = LV_COLOR_WHITE;
  style_bg.body.padding.hor = 12;
  style_bg.body.padding.ver = 8;
  style_bg.body.shadow.width = 8;
  lv_obj_t * background = lv_page_create(lv_scr_act(), NULL);
  lv_page_set_style(background, LV_PAGE_STYLE_BG, &style_bg);
}

void Display::createBatteryMeter(void){
  sys_battery_meter = lv_lmeter_create(disabled_tab, NULL);
  bat_meter_label = lv_label_create(sys_battery_meter, NULL);
  lv_obj_t * symbol_label =  lv_label_create(sys_battery_meter, NULL);
  lv_lmeter_set_range(sys_battery_meter, 0, 100);
//  lv_obj_set_size(sys_battery_meter, 80, 80);
  lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_CENTER, 25, -15);
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
  lv_obj_t*directionSwitch = lv_sw_create(motor_test_tab, NULL);
  lv_obj_t*OnOffLabel = lv_label_create(OnOffSwitch, NULL);
  lv_obj_t*directionLabel = lv_label_create(directionSwitch, NULL);

  lv_sw_set_action(OnOffSwitch, oo_switch_action);
  lv_sw_set_action(directionSwitch, fb_switch_action);

  lv_label_set_text(directionLabel, "<BCK : FWD>");
  lv_label_set_text(OnOffLabel, "<OFF : ON>");

  lv_obj_align(OnOffSwitch, NULL, LV_ALIGN_IN_TOP_RIGHT, -25, -25);
  lv_obj_align(directionSwitch, NULL, LV_ALIGN_IN_TOP_RIGHT, -25, -50);
  lv_obj_set_width(motorSelect, 120); //sets the width of our ddlist
  lv_obj_align(motorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 0 , -25);
  lv_ddlist_set_options(motorSelect, "BaseFL\nBaseFR\nBaseBL\nBaseBR\nLift1\nLift2\n");
  lv_ddlist_set_action(motorSelect, dropDown_action);
  lv_ddlist_set_sb_mode(motorSelect, LV_SB_MODE_ON);
}
void Display::motorTest(void)
{
  //if the on switch is on, move the motor a direction multiplied by the forward switch
  //moves the motor at index i, where i is the element selected from the drop down menu
  SystemMotors[currentTestMotor].move(
    (on ? 67 : 0 ) *
    (fwd ? 1 : -1)
  );

}

void Display::refresh(void)
{
//  lv_lmeter_set_value(sys_battery_meter, pros::battery::get_capacity()); //standin
  switch(lv_tabview_get_tab_act(tabs)){ //switch case statement that will only update values for active tab
    case TAB_DISPLAY: //Main Tab for Displaying Match info and Logo
      if(button.get_value()){lv_led_on(frontLED);} //If the front light sensor reading is less than 2700, turn on the LED
      else{lv_led_off(frontLED);} //Otherwise it is off
      if(LiftL.get_actual_velocity() > 550){lv_led_on(fwLED);} //If the actualy flywheel velocity is greater than 550, turn on the LED
      else{lv_led_off(fwLED);} //Otherwise it is off
      if(LightSensor.get_value() < 2700){lv_led_on(backLED);} //If the back light sensor reading is less than 2700, turn on the LED
      else{lv_led_off(backLED);} //Otherwise it is off

    case TAB_INFO: //Information Tab with battery levels and other Information
      int level = pros::battery::get_capacity();
      lv_lmeter_set_value(sys_battery_meter, level);

      lv_label_set_text(bat_meter_label, (std::to_string(level)+"%").c_str()); //convert level(int) to string to a const char
      lv_label_set_text(gyroLabel, (std::to_string(gyro.get_value()) + "°").c_str());

      lv_gauge_set_value(gyroGauge, 0, (gyro.get_value() == 0 ? gyro.get_value() : gyro.get_value() + 20)); //Sets our gauge position to be the gyro position
  }
//  lv_lmeter_set_value(bat_meter_label, level);


  delay(20);
}

void Display::setActiveTab(int tab){
  lv_tabview_set_tab_act(tabs, tab, LV_ANIM_NONE);
}

void Display::createScreen(void)
{
    lv_theme_t *th = lv_theme_alien_init(60, NULL); //Sets the theme, 60 For TTYellow
    lv_tabview_set_sliding(tabs, false);
  //  lv_tabview_get_style(tabs, LV_TABVIEW_STYLE_BTN_PR);
    lv_tabview_set_anim_time(tabs, 0); //Disable animations to save the brain

    //Call our functions
    create1010Image();
    createBatteryMeter();
    createOpLEDs();
    createGauge();
    createAutoSelector();
    createMotorTest();
  //  createBackground();
}
