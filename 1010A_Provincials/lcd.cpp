 #include "main.h"
//#include "flywheel.h"
//define variables
//most of these are externs that are accessed by other files
int currentAuto = 0; //used in autonomous.c
int currentSpeed; //not currently used
bool LCD_Roller; //if the roller on checkbox button has been pressed in lcd.cpp
bool LCD_LP; //if the inside roller on checkbox button has been pressed in lcd.cpp
bool LCD_Angle;
int LCD_Direction = DIRECTION_FORWARD; //used in opcontrol.c
int Roller_speed = Roller_speed;
double startingPosition = angler.get_position();
double startingPositionCap = capStack.get_position();
 //use rmtr for invert
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
    else if((strcmp(lv_cb_get_text(cb), "Linear Puncher") == 0)){ //compares the string ID of selected box to String constant
        LCD_LP = true; //turns on inside roller
    }
    else if((strcmp(lv_cb_get_text(cb), "Angle Controller") == 0)){ //compares the string ID of selected box to String constant
        LCD_Angle = true; //turns on inside roller
    }
  }
  else{
    //if((strcmp(lv_cb_get_text(cb), "Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_Roller = false; //turns on roller
  //  }
  //  else if((strcmp(lv_cb_get_text(cb), "Inside Roller") == 0)){ //compares the string ID of selected box to String constant
        LCD_LP = false; //turns off Linear puncher

        LCD_Angle = false;
    }
//  }
  /*  else{
      LCD_Roller = false; //turn off roller
      LCD_LP = false; //turn off inside roller
    }*/


    return LV_RES_OK; //return an OK Status after execution
}

void LCD_Task_fn(void * parameter){ //start running the task
  auto angleController = okapi::AsyncControllerFactory::posIntegrated(AnglerPORT);
  auto capController = okapi::AsyncControllerFactory::posIntegrated(CapPORT);

  lv_theme_t *th = lv_theme_alien_init(0, NULL); //initialize global 'alien' theme with an HSV on 120, which would yield green
  lv_obj_t *tabview; //start up tab view
  tabview = lv_tabview_create(lv_scr_act(), NULL);

  //Add 3 tabs (the tabs are page (lv_page) and can be scrolled
  lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Home"); //second tab
  lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Auto Set"); //first tab
  lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Motor Test"); //third tab
  lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "Data");

/*  lv_obj_t *dataTab = lv_tabview_create(tab4, NULL);
  lv_obj_t *autoTab = lv_tabview_add_tab(dataTab, "Autonomous");
  lv_obj_t *opTab = lv_tabview_add_tab(dataTab, "Operator Control");

*/

//setting style
  static lv_style_t style_border;
  lv_style_copy(&style_border, &lv_style_pretty_color);
  style_border.glass = 1;
  style_border.body.empty = 1;

/*************
***TAB ONE***
*************/
lv_obj_t *AutoRoller = lv_roller_create(tab2, NULL); //creates a roller on tab1 for auto selection
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

lv_obj_t * autoled = lv_led_create(tab2, NULL);
lv_obj_align(autoled, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);
lv_obj_set_size(autoled, 20, 20);
//add label to second led
lv_obj_t * auto_label = lv_label_create(tab2, NULL);
//auto_label = lv_label_create(tab1, NULL);
lv_label_set_text(auto_label, "Autonomous");
lv_obj_align(auto_label, autoled, LV_ALIGN_OUT_LEFT_MID, 130, 0);
/*************
***TAB TWO***
*************/
static lv_color_t needle_colors[] = {LV_COLOR_BLUE, LV_COLOR_ORANGE, LV_COLOR_PURPLE, LV_COLOR_RED, LV_COLOR_AQUA}; //array for needle colours

/*Create a gauge*/
lv_obj_t * gauge1 = lv_gauge_create(tab1, NULL); //create a gauge for the angler position
lv_obj_set_size(gauge1, 185, 185);
//lv_gauge_set_style(gauge1, &style);
lv_gauge_set_range(gauge1,  (startingPosition - 125), (startingPosition));
lv_gauge_set_critical_value(gauge1, (startingPosition - 75));
lv_gauge_set_needle_count(gauge1, 5, needle_colors);
lv_obj_align(gauge1, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 50, 190);

/*Set the values*/
lv_gauge_set_value(gauge1, 0, (startingPosition));
lv_gauge_set_value(gauge1, 1, (startingPosition - 100));
lv_gauge_set_value(gauge1, 2, (startingPosition - 45));
lv_gauge_set_value(gauge1, 3, (startingPosition - 80));

//roller output level bar
lv_obj_t * rollerBar = lv_bar_create(tab1, NULL); //create a bar on tab two
lv_obj_set_size(rollerBar, 125, 25);//set bar's size to 200X and 25Y
lv_obj_align(rollerBar, NULL, LV_ALIGN_IN_TOP_RIGHT, -8, 35); //align in top left with an additional 50 down
lv_bar_set_range(rollerBar, -12000, 12000); //sets range of bar

lv_obj_t * rBarLabel = lv_label_create(tab1, NULL); //creates a label for the bar
lv_label_set_text(rBarLabel, "Roller"); //sets the text of the label
lv_obj_align(rBarLabel, rollerBar, LV_ALIGN_CENTER, 0, 0); //aligns the label to the center of the bar

//creates a bar for the inside roller the same way we made one for the normal roller
/*lv_obj_t * linearPBar = lv_bar_create(tab1, NULL);
lv_obj_set_size(linearPBar, 200, 25);
lv_obj_align(linearPBar, rollerBar, LV_ALIGN_CENTER, 0, 35);
lv_bar_set_range(linearPBar, -12000, 12000);*/


/*lv_obj_t * IrBarLabel = lv_label_create(tab1, NULL);
lv_label_set_text(IrBarLabel, "Inside Roller");
lv_obj_align(IrBarLabel, linearPBar, LV_ALIGN_CENTER, 0, 0);
*/

lv_obj_t * label = lv_label_create(tab1, NULL); //Create a home screen label on tab1
lv_label_set_text(label, "1010A Robot - Home"); //sets the text
lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0); //aligns the home screen to top middle area of tab1

lv_obj_t * sys_battery_meter;
sys_battery_meter = lv_lmeter_create(tab1, NULL);
lv_lmeter_set_range(sys_battery_meter, 0, 100);
lv_obj_set_size(sys_battery_meter, 120, 120);

lv_obj_t * bat_meter_label;
lv_obj_align(sys_battery_meter, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
bat_meter_label = lv_label_create(sys_battery_meter, NULL);
lv_obj_align(bat_meter_label, sys_battery_meter, LV_ALIGN_CENTER, -6, -11);
lv_label_set_text(bat_meter_label, "Battery");
//lv_obj_set_pos(bat_meter_label, 200, -75);
lv_obj_t * symbol_label_1;
symbol_label_1 = lv_label_create(sys_battery_meter, NULL); //Create a label on tab1 for the battery level
//lv_label_set_style(label, &lv_style_pretty);
lv_obj_align(symbol_label_1, bat_meter_label, LV_ALIGN_CENTER, 0, 14); //aligns to the meter label

lv_obj_t * gyro_meter;
gyro_meter = lv_lmeter_create(tab1, NULL);
lv_lmeter_set_range(gyro_meter, 0, 360);
lv_obj_set_size(sys_battery_meter, 120, 120);

lv_obj_t * gyro_meter_label;
gyro_meter_label = lv_label_create(gyro_meter_label, NULL);
lv_obj_align(gyro_meter_label, gyro_meter, LV_ALIGN_CENTER, -6, -11);
lv_label_set_text(gyro_meter, "Gyro Value");

/**************
***TAB THREE***
***************/

lv_obj_t * opled = lv_led_create(tab3, NULL); //creates led
lv_obj_align(opled, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, 40); //aligns led in bottom left with additional 10 in the X and 40 in the Y
lv_obj_set_size(opled, 20, 20); //sets size

lv_obj_t * op_label = lv_label_create(tab3, NULL); //add label to second led
lv_label_set_text(op_label, "Controller"); //set label text
lv_obj_align(op_label, opled, LV_ALIGN_OUT_LEFT_MID, 130, 0); //aligns led in left middle with additional 130 in the X

lv_obj_t * op2led = lv_led_create(tab3, NULL); //creates second led
lv_obj_align(op2led, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -25); //aligns led in bottom left with additional 10 in the X and -25 in the Y
lv_obj_set_size(op2led, 20, 20); //sets size

lv_obj_t * op2_label = lv_label_create(tab3, NULL); //add label to second led
//op_label = lv_label_create(tab1, NULL);
lv_label_set_text(op2_label, "Partner Controller"); //sets label text
lv_obj_align(op2_label, op2led, LV_ALIGN_OUT_LEFT_MID, 210, 0); //aligns led in left middle with additional 210 in the X


lv_obj_t *forwardSwitch = lv_sw_create(tab3, NULL); //create switch
lv_obj_align(forwardSwitch, NULL, LV_ALIGN_IN_LEFT_MID, 10, -50); //align switch
lv_obj_set_size(forwardSwitch, 70, 35);
lv_sw_on(forwardSwitch); //set defaul state to on
lv_sw_set_action(forwardSwitch, switch_action); //sets action to switch action to the switch action function

/*lv_obj_t * FW_cont;  // Create a container for the check boxes
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
*/
lv_obj_t * cont; //creates another container like above ^
cont = lv_cont_create(tab3, NULL);
lv_cont_set_layout(cont, LV_LAYOUT_COL_L);
lv_cont_set_fit(cont, true, true); //doesn't fit column size
lv_obj_set_style(cont, &style_border);
lv_obj_align(cont, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0); //aligns to left mid with flywheel boxes and an X of -145 and a Y of 20
/**************************
 * Create check boxes
 *************************/
lv_obj_t * cb;
cb = lv_cb_create(cont, NULL); //create option
lv_cb_set_text(cb, "Roller"); //create ID
lv_cb_set_action(cb, cb_release_action); //set action to action function

cb = lv_cb_create(cont, cb); //create option
lv_cb_set_text(cb, "Linear Puncher");//create ID

cb = lv_cb_create(cont, cb); //create option
lv_cb_set_text(cb, "Angle Controller");//create ID


/**************
***TAB FOUR***
***************/
lv_obj_t * AngleChart; //creates chart for Angler PID
AngleChart = lv_chart_create(tab4, NULL);
lv_obj_set_size(AngleChart, 200, 150); //sets chart size to 200x150
lv_chart_set_type(AngleChart, LV_CHART_TYPE_LINE); //sets chart Type to a solid line (can also be dotted)
lv_chart_set_series_opa(AngleChart, LV_OPA_70); //sets the opacity of the chart to the standard value
lv_chart_set_series_width(AngleChart, 5); //sets the series width to 5 squares
lv_chart_set_range(AngleChart,-30, 120); //sets the range of values to -30 as the minimum and 120 as the maximum
lv_chart_series_t * angle_position_series = lv_chart_add_series(AngleChart, LV_COLOR_AQUA); //adds a series for the current position
lv_chart_series_t * angle_target_series = lv_chart_add_series(AngleChart, LV_COLOR_ORANGE); //adds a series for the target position
lv_chart_series_t * angle_position_error = lv_chart_add_series(AngleChart, LV_COLOR_RED); //adds a series for the current error

lv_obj_t * joystickChart; //creates chart for Joystick Values
joystickChart = lv_chart_create(tab4, NULL);
lv_obj_align(joystickChart, NULL, LV_ALIGN_IN_RIGHT_MID, -50, -30); //aligns in right middle with adjustment of -50X and -30Y
lv_obj_set_size(joystickChart, 200, 150); //sets chart size to 200x150
lv_chart_set_type(joystickChart, LV_CHART_TYPE_LINE); //sets chart Type to a solid line (can also be dotted)
lv_chart_set_series_opa(joystickChart, LV_OPA_70); //sets the opacity of the chart to the standard value
lv_chart_set_series_width(joystickChart, 5); //sets the series width to 5 squares
lv_chart_set_range(joystickChart,0, 2000); //sets the range of values to -127 as the minimum and 127 as the maximum
lv_chart_series_t * joystick_3_val = lv_chart_add_series(joystickChart, LV_COLOR_BLUE); //adds series for the Ch3 Axis
lv_chart_series_t * joystick_4_val = lv_chart_add_series(joystickChart, LV_COLOR_PURPLE); //adds series for the Ch4 Axis
lv_chart_series_t * joystick_1_val = lv_chart_add_series(joystickChart, LV_COLOR_GREEN); //adds series for the Ch1 Axis
lv_chart_series_t * joystick_2_val = lv_chart_add_series(joystickChart, LV_COLOR_LIME); //adds series for the Ch2 Axis

delay(500); //delay 100ms before startng loop


while(true){ //main loop
  //move some opcontrol here, because that's how the mafia works
/*
  if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){ //middle flag 1
    angleController.setTarget((startingPosition - 80)); //sets angler position to -80
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){ //top flag and default
    angleController.setTarget((startingPosition));
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
    angleController.setTarget((startingPosition - 45));
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
    angleController.setTarget((startingPosition - 90));
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_A)){
    angleController.setTarget((startingPosition - 62));
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_B)){
    angleController.setTarget((startingPosition - 75));
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
    angleController.setTarget((startingPosition - 25));
  }

  if(master.get_digital(E_CONTROLLER_DIGITAL_UP)){
    capController.setTarget(startingPositionCap + 1460);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
    capController.setTarget(startingPositionCap);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
    capController.setTarget(startingPositionCap + 1710);
  }
  else if(master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
    capController.setTarget(startingPositionCap + 570);
  }
*/
  //variables for tab control, that saves the brain from crippling depression
  int active = lv_tabview_get_tab_act(tabview);
if(active == 0){
    int level = pros::battery::get_capacity(); //sets variable to battery level
    int value = abs(gyroM.get_value());

    if(master.is_connected()){lv_led_on(opled);} //if controller is on turn on the LED we defined earlier
    else{lv_led_off(opled);} //otherwise it is off

    if(pros::competition::is_autonomous()){lv_led_on(autoled);} //if autonomous is enaabled turn on the LED we defined earlier
    else{lv_led_off(autoled);} //otherwise it is off

    if(partner.is_connected()){lv_led_on(op2led);}
    else{lv_led_off(op2led);} //otherwise it is off

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

    lv_lmeter_set_value(gyro_meter, value); //sets the previously defined dial to the gyro readings
    lv_gauge_set_value(gauge1, 4, angler.get_position());
    lv_lmeter_set_value(sys_battery_meter, level); //sets the wheel we made earlier to battery level
    lv_bar_set_value(rollerBar,  Roller.get_voltage()); //sets the bar we made earlier to the roller voltage level

}
else if(active == 3){
  auto AngleTarget = abs(angleController.getTarget());
  auto angle_pos = abs(angler.get_position());
  auto angle_error = angleController.getError();
  auto CapTarget = abs(capController.getTarget());
  auto cap_pos = abs(capStack.get_position());
  auto cap_error = capController.getError();

  lv_chart_set_next(AngleChart, angle_target_series, AngleTarget);
  lv_chart_set_next(AngleChart, angle_position_series, angle_pos);
  lv_chart_set_next(AngleChart, angle_position_error, angle_error);
  lv_chart_refresh(AngleChart);

  lv_chart_set_next(joystickChart, joystick_4_val, CapTarget);
  lv_chart_set_next(joystickChart, joystick_3_val, cap_pos);
  lv_chart_set_next(joystickChart, joystick_2_val, cap_error);
  lv_chart_refresh(joystickChart);
}
  Task::delay(100);//loop infinitely
  delay(100);
  }
  Task::delay(100);
  delay(100);
}
