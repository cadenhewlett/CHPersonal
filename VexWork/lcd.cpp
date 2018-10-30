#include "main.h"
#include "flywheel.h"
//#include "variables.h"
//define variables
//most of these are externs that are accessed by other files
int currentAuto = 0; //used in autonomous.c
int currentSpeed; //not currently used

bool LCD_Roller; //if the roller on checkbox button has been pressed in lcd.cpp
bool LCD_InsideRoller; //if the inside roller on checkbox button has been pressed in lcd.cpp
bool LCD_FWheelMax; //if the flywheel max checkbox button has been pressed in lcd.cpp
bool LCD_FWheelMed; //if the flywheel medium checkbox button has been pressed in lcd.cpp
bool LCD_FWheelLow; //if the flywheel low checkbox button has been pressed in lcd.cpp
bool LCD_FWheelOff; //if the flywheel off checkbox button has been pressed in lcd.cpp
int LCD_Direction = DIRECTION_FORWARD; //used in opcontrol.c
int Roller_speed = Roller_speed;
//init controller
okapi::Controller controller;
okapi::Motor Roller = 5_mtr;
okapi::Motor InsideRoller = 6_mtr; //use rmtr for invert
//define action functions for various objects
//these action functions allow for more versatility and consistency in the program
//it also allows for the use of multiple buttons, wheels, etc. without needing lots of hard-coding

static lv_res_t switch_action(lv_obj_t * swtch){ //switch action function
  if(lv_sw_get_state(swtch) == /* not needed */ true ){   //if the switch is on
    LCD_Direction = DIRECTION_FORWARD; //move the LCD Test motors in the forward direction
  }
  else{ //if the switch is off
    LCD_Direction = DIRECTION_BACKWARD; //move the LCD Test motors in the backward direction
  }
  return LV_RES_OK; //return an OK Status after execution
}
static lv_res_t autoSelect_action(lv_obj_t * roller) //Auto selection roller action function
{
  currentAuto = lv_roller_get_selected(roller); //current auto becomes the integer ID of the selected value
                                                //this means that if "None" is selected, this will be ID 0

  return LV_RES_OK; //return an OK Status after execution
}
static lv_res_t cb_release_action(lv_obj_t * cb) //check box action func.
{
  // BUG currently deselecting 1 turns off everything - this may be fixed by doing a
  // BUG try fixing with strcmp(a, "b") == 1 for deselection , where a is text box and b is string ID
  /*  printf("%s state: %d\n", lv_cb_get_text(cb), lv_cb_is_checked(cb));*/
  if(lv_cb_is_checked(cb)){
    if((strcmp(lv_cb_get_text(cb), "Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_Roller = true; //turns on roller
    }
    else if((strcmp(lv_cb_get_text(cb), "Inside Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_InsideRoller = true; //turns on inside roller
    }
  }
  else if(!(lv_cb_is_checked(cb))){
    if((strcmp(lv_cb_get_text(cb), "Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_Roller = false; //turns on roller
    }
    else if((strcmp(lv_cb_get_text(cb), "Inside Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_InsideRoller = true; //turns on inside roller
    }
  }
  /*  else{
      LCD_Roller = false; //turn off roller
      LCD_InsideRoller = false; //turn off inside roller
    }*/


    return LV_RES_OK; //return an OK Status after execution
}
static lv_res_t fw_cb_release_action(lv_obj_t * FWcb) //flywheel check box action func.
{
  // BUG : Deselecting any option turns off the flywheel immediately
  // this is partially for safety reasons, partially because I don't know how to fix it yet
  if(lv_cb_is_checked(FWcb) == 1){ //if a check box is selected
    if(strcmp(lv_cb_get_text(FWcb), "Flywheel Max") == 0){ //ask if it has an ID of "Flywheel Max"
      LCD_FWheelMax = true; //if it does, flywheel max becomes true
    }
    else if(strcmp(lv_cb_get_text(FWcb), "Flywheel Med") == 0){  //otherwise ask if it has an ID of "Flywheel Med"
      LCD_FWheelMed = true;  //if it does, flywheel med becomes true
    }
    else if(strcmp(lv_cb_get_text(FWcb), "Flywheel Low") == 0){ //same sort of pattern as above
      LCD_FWheelLow = true;
    }
    else if(strcmp(lv_cb_get_text(FWcb), "Flywheel Off") == 0){ //if the compared ID matches none of the above
      LCD_FWheelOff = true; //turn off the flywheel
    }
    else{
      LCD_FWheelOff = true;
    }
  }
  else{
    //otherwise turn everything off
    LCD_FWheelMax = false;
    LCD_FWheelMed = false;
    LCD_FWheelLow = false;
    LCD_FWheelOff = true;
  }
  return LV_RES_OK; //return an OK Status after execution
}

void LCD_Task_fn(void * parameter){ //start running the task

  lv_theme_t *th = lv_theme_alien_init(120, NULL); //initialize global 'alien' theme with an HSV on 120, which would yield green

  lv_obj_t *tabview; //start up tab view
  tabview = lv_tabview_create(lv_scr_act(), NULL);

  //Add 3 tabs (the tabs are page (lv_page) and can be scrolled
  lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Auto Set"); //first tab
  lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Home"); //second tab
  lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Motor Test"); //third tab
  //to add another tab, use the above function with tabview as the parent tab


//setting style
  static lv_style_t style_border;
  lv_style_copy(&style_border, &lv_style_pretty_color);
  style_border.glass = 1;
  style_border.body.empty = 1;

/*************
***TAB ONE***
*************/
lv_obj_t *AutoRoller = lv_roller_create(tab1, NULL); //creates a roller on tab1 for auto selection
lv_roller_set_options(AutoRoller, //defines the options for the roller. \n is a page break to divide options
  "None\n"
  "Blue Caps\n"
  "Blue Flags\n"
  "Red Caps\n"
  "Red Flags\n"
  "Skills"
);
lv_obj_set_size(AutoRoller, 50, 150); //sets autoroller size size - changing x value doesn't seem to make it wider
lv_roller_set_action(AutoRoller, autoSelect_action); //sets the autoroller action to our autoroller function from earlier.
                                                    // The function will now run every time the roller value is changed
lv_obj_align(AutoRoller, NULL, LV_ALIGN_CENTER, 0, 0); //aligns the roller to the center of tab1

lv_obj_t * SelectedLabel = lv_label_create(tab1, NULL); //Create a label on tab1
lv_obj_align(SelectedLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0); //aligns the selected auto label to top right


lv_obj_t * autoled = lv_led_create(tab1, NULL);
lv_obj_align(autoled, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);
lv_obj_set_size(autoled, 20, 20);
//add label to second led
lv_obj_t * auto_label = lv_label_create(tab1, NULL);
auto_label = lv_label_create(tab1, NULL);
lv_label_set_text(auto_label, "Autonomous");
lv_obj_align(auto_label, autoled, LV_ALIGN_OUT_LEFT_MID, 130, 0);
/*************
***TAB TWO***
*************/

//roller output level bar
lv_obj_t * rollerBar = lv_bar_create(tab2, NULL); //create a bar on tab two
lv_obj_set_size(rollerBar, 200, 25);//set bar's size to 200X and 25Y
lv_obj_align(rollerBar, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50); //align in top left with an additional 50 down
lv_bar_set_range(rollerBar, -12000, 12000); //sets range of bar

lv_obj_t * rBarLabel = lv_label_create(tab2, NULL); //creates a label for the bar
lv_label_set_text(rBarLabel, "Roller"); //sets the text of the label
lv_obj_align(rBarLabel, rollerBar, LV_ALIGN_CENTER, 0, 0); //aligns the label to the center of the bar

//creates a bar for the inside roller the same way we made one for the normal roller
lv_obj_t * insideRollerBar = lv_bar_create(tab2, NULL);
lv_obj_set_size(insideRollerBar, 200, 25);
lv_obj_align(insideRollerBar, rollerBar, LV_ALIGN_CENTER, 0, 35);
lv_bar_set_range(insideRollerBar, -12000, 12000);

lv_obj_t * IrBarLabel = lv_label_create(tab2, NULL);
lv_label_set_text(IrBarLabel, "Inside Roller");
lv_obj_align(IrBarLabel, insideRollerBar, LV_ALIGN_CENTER, 0, 0);


lv_obj_t * label = lv_label_create(tab2, NULL); //Create a home screen label on tab2
lv_label_set_text(label, "1010A Robot - Home"); //sets the text
lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0); //aligns the home screen to top middle area of tab2

//Create the Indicator LEDs
/*lv_obj_t * autoled = lv_led_create(tab2, NULL); //create led on tab2
lv_obj_align(autoled, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 40); //aligns led to top left and moves it an additional 10x and 40y
*/
//Add label to first LED
/*lv_obj_t * auto_led_label = lv_label_create(tab2, NULL);
lv_label_set_text(auto_led_label, "Autonomous");
lv_obj_align(auto_led_label, autoled, LV_ALIGN_OUT_LEFT_MID, 150, 0);
*/

//connected led

lv_obj_t * opled = lv_led_create(tab2, NULL);
lv_obj_align(opled, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, 40);
lv_obj_set_size(opled, 20, 20);
//add label to second led
lv_obj_t * op_label = lv_label_create(tab2, NULL);
op_label = lv_label_create(tab2, NULL);
lv_label_set_text(op_label, "Controller");
lv_obj_align(op_label, opled, LV_ALIGN_OUT_LEFT_MID, 130, 0);

/*Create a new style*/
static lv_style_t style_lmeter2;
lv_style_copy(&style_lmeter2, &lv_style_pretty_color);
style_lmeter2.line.width = 2;
style_lmeter2.line.color = LV_COLOR_SILVER;
style_lmeter2.body.padding.hor = 8;            //line length
style_lmeter2.body.main_color = LV_COLOR_RED;
style_lmeter2.body.grad_color = LV_COLOR_LIME;

lv_obj_t * sys_battery_meter;
sys_battery_meter = lv_lmeter_create(tab2, NULL);
lv_lmeter_set_range(sys_battery_meter, 0, 100);
lv_obj_set_size(sys_battery_meter, 120, 120);

lv_obj_t * bat_meter_label;
lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -20, 10);
bat_meter_label = lv_label_create(sys_battery_meter, NULL);
lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, -6, -11);
lv_label_set_text(bat_meter_label, "Battery");
//lv_obj_set_pos(bat_meter_label, 200, -75);
lv_obj_t * symbol_label_1;
symbol_label_1 = lv_label_create(sys_battery_meter, NULL);
//lv_label_set_style(label, &lv_style_pretty);
lv_obj_align(symbol_label_1, bat_meter_label, LV_ALIGN_CENTER, -2, 14);


/**************
***TAB THREE***
***************/
lv_obj_t *forwardSwitch = lv_sw_create(tab3, NULL); //create switch
lv_obj_align(forwardSwitch, NULL, LV_ALIGN_IN_LEFT_MID, 10, -50); //align switch
lv_sw_on(forwardSwitch); //set defaul state to on
lv_sw_set_action(forwardSwitch, switch_action); //sets action to switch action to the switch action function

lv_obj_t * FW_cont;  // Create a container for the check boxes
FW_cont = lv_cont_create(tab3, NULL);
lv_cont_set_layout(FW_cont, LV_LAYOUT_COL_L);   //sets container to a column
lv_cont_set_fit(FW_cont, true, true);   //sizes container to content(if true and true)
//lv_obj_set_style(FW_cont, &style_border); //sets style
lv_obj_align(FW_cont, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0); //aligns in right mid with -50 additional X

lv_obj_t * FWcb; //creates checkbox
FWcb = lv_cb_create(FW_cont, NULL);
lv_cb_set_text(FWcb, "Flywheel Max"); //add options to checkbox
lv_cb_set_action(FWcb, fw_cb_release_action); //set checkbox action to action function

FWcb = lv_cb_create(FW_cont, NULL); //add option to checkbox
lv_cb_set_text(FWcb, "Flywheel Med"); //ad ID

FWcb = lv_cb_create(FW_cont, NULL);//add option
lv_cb_set_text(FWcb, "Flywheel Low");//add ID

FWcb = lv_cb_create(FW_cont, NULL);//add option
lv_cb_set_text(FWcb, "Flywheel Off");//add ID
lv_cb_set_checked(FWcb, true); //defaults to on

lv_obj_t * cont; //creates another container like above ^
cont = lv_cont_create(tab3, NULL);
lv_cont_set_layout(cont, LV_LAYOUT_COL_L);
lv_cont_set_fit(cont, false, false); //doesn't fit column size
lv_obj_set_style(cont, &style_border);
lv_obj_align(cont, FW_cont, LV_ALIGN_IN_LEFT_MID, -145, 20); //aligns to left mid with flywheel boxes and an X of -145 and a Y of 20
/**************************
 * Create check boxes
 *************************/
lv_obj_t * cb;
cb = lv_cb_create(cont, NULL); //create option
lv_cb_set_text(cb, "Roller"); //create ID
lv_cb_set_action(cb, cb_release_action); //set action to action function

cb = lv_cb_create(cont, cb); //create option
lv_cb_set_text(cb, "Inside Roller");//create ID

delay(100);
while(true){ //main loop
  int level = pros::battery::get_capacity(); //sets variable to battery level
  if(controller.isConnected()){lv_led_on(opled);} //if controller is on turn on the LED we defined earlier
  else{lv_led_off(opled);} //otherwise it is off
  if(pros::competition::is_autonomous()){lv_led_on(autoled);} //if autonomous is enaabled turn on the LED we defined earlier
  else{lv_led_off(autoled);} //otherwise it is off
  if(level<10){ //ranges of battery levels
    lv_label_set_text(symbol_label_1, SYMBOL_BATTERY_EMPTY); //less than 10%
  }else if(level<25){
    lv_label_set_text(symbol_label_1, SYMBOL_BATTERY_1); //less than 25% is one-quarter full battery symbol
  }else if(level<60){
    lv_label_set_text(symbol_label_1, SYMBOL_BATTERY_2); //less than 60% is half-way battery symbol
  }else if(level<85){
    lv_label_set_text(symbol_label_1, SYMBOL_BATTERY_3); //less than 85% is three-quarters full battery symbol
  }else if(level>85){
    lv_label_set_text(symbol_label_1, SYMBOL_BATTERY_FULL); //more than 85% is a battery full symbol
  }
  lv_lmeter_set_value(sys_battery_meter, level); //sets the wheel we made earlier to battery level
  lv_bar_set_value(rollerBar,  Roller.getVoltage()); //sets the bar we made earlier to the roller voltage level
  lv_bar_set_value(insideRollerBar, InsideRoller.getVoltage());//sets the other bar we made earlier to the inside roller voltage level
  delay(100);//loop infinitely
  }
}
