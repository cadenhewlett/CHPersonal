#include "main.h"
#include "display.h"
#include <string.h>

extern const lv_img_t test_detail;
extern const lv_img_t logo;

extern lv_obj_t*tabs;
extern lv_obj_t*auto_op_tab;
extern lv_obj_t*disabled_tab;
extern lv_obj_t*test_tab;
extern lv_obj_t*gyroGauge;
extern lv_obj_t * frontLED;

lv_res_t autoSelect_action(lv_obj_t * selector) /*creates list action*/
{
  currentAuto = lv_roller_get_selected(selector); /*Changes the current auto to be the list option index*/

  return LV_RES_OK;
}

lv_res_t switch_action(lv_obj_t*swtch)
{

  if(lv_sw_get_state(swtch) == SWITCH_FORWARD)
  {

  }
  else
  {

  }
  return LV_RES_OK;
}

lv_obj_t*tabs = lv_tabview_create(lv_scr_act(), NULL);
lv_obj_t * auto_op_tab = lv_tabview_add_tab(tabs, "Enabled");
lv_obj_t * disabled_tab = lv_tabview_add_tab(tabs, "Disabled");
lv_obj_t * test_tab = lv_tabview_add_tab(tabs, "BALLS");
lv_obj_t * frontLED;
lv_obj_t * backLED;
lv_obj_t * fwLED;
lv_obj_t * gyroGauge; //create a gauge for the angler position

void Display::imageTest(void)
{
  LV_IMG_DECLARE(logoNew);
  lv_obj_t * img2 = lv_img_create(auto_op_tab, NULL); //create the new image
  lv_img_set_src(img2, &logoNew);//sets the source of the image to be the array from the C File
  lv_obj_align(img2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 0); //align the image
//  lv_obj_set_size(img2, 130, 170);
}
void Display::imageTest2(void)
{
  LV_IMG_DECLARE(test_detail); //declare from our C File
  lv_obj_t * img1 = lv_img_create(test_tab, NULL); //create the new image
  lv_img_set_src(img1, &test_detail);//sets the source of the image to be the array from the C File
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0); //align the image
}

void Display::createTitle(void)
{
  lv_obj_t * title =  lv_label_create(disabled_tab, NULL); //Create a Label on the currently active screen
  lv_label_set_text(title, "Ten Ton Robotics - TEST"  );//Sets the text of the label
  lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 5); //Align object
}

void Display::createOpLEDs(void)
{
  frontLED = lv_led_create(auto_op_tab, NULL);
  backLED = lv_led_create(auto_op_tab, NULL);
  fwLED = lv_led_create(auto_op_tab, NULL);
  lv_obj_t * frontLabel = lv_label_create(auto_op_tab, NULL);
  lv_obj_t * backLabel = lv_label_create(auto_op_tab, NULL);
  lv_obj_t * fwLabel = lv_label_create(auto_op_tab, NULL);
  lv_obj_align(frontLED, NULL, LV_ALIGN_IN_TOP_RIGHT, -63, 68);
  lv_obj_align(backLED, frontLED, LV_ALIGN_CENTER, 0, 55);
  lv_obj_align(fwLED, backLED, LV_ALIGN_CENTER, 0, 55);
  lv_obj_align(frontLabel, frontLED, LV_ALIGN_CENTER, 60, 0);
  lv_obj_align(backLabel, backLED, LV_ALIGN_CENTER, 60, 0);
  lv_obj_align(fwLabel, fwLED, LV_ALIGN_CENTER, 60, 0);
  lv_label_set_text(frontLabel, "FLS");
  lv_label_set_text(backLabel, "BLS");
  lv_label_set_text(fwLabel, "FW");
  lv_led_off(frontLED);
  lv_led_off(backLED);
  lv_led_off(fwLED);
}

void Display::createGauge()
{
  static lv_color_t needle_colors[] = {LV_COLOR_RED}; //array for needle colours

  /*Create a gauge*/
  gyroGauge = lv_gauge_create(disabled_tab, NULL); //create a gauge for the angler position
  //lv_gauge_set_style(gyroGauge, &style);
  lv_gauge_set_scale(gyroGauge, 360, 18, 9);
  lv_gauge_set_range(gyroGauge,  0, 3600);
  lv_gauge_set_critical_value(gyroGauge, 2700);
  lv_gauge_set_needle_count(gyroGauge, 1, needle_colors);
  lv_obj_set_size(gyroGauge, 180, 180);
  lv_obj_align(gyroGauge, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);
  lv_obj_set_y(gyroGauge, -10);
}

void Display::createAutoSelector(void)
{
  lv_obj_t * autoSelector = lv_roller_create(disabled_tab, NULL); //create auto selector
  lv_roller_set_options(autoSelector, "Red\nBlue\nRed Front\nSkills\nOther\nMore"); //sets options to our character array
  lv_obj_set_width(autoSelector, 120); //sets the widtho of our list
  lv_roller_set_visible_row_count(autoSelector, 4);
  lv_roller_set_action(autoSelector, autoSelect_action); //Sets the action to our previously defined function
  lv_obj_align(autoSelector, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 10); //Align object
  lv_obj_set_y(autoSelector, 35);
}

void Display::createSwitch(void)
{
  lv_obj_t * testSwitch = lv_sw_create(lv_scr_act(), NULL);//create switch
  lv_sw_set_action(testSwitch, switch_action);//set function to be our previously defined function
  lv_obj_align(testSwitch, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -15); //aligns the switch to the bottom left
  lv_obj_t * switchLabel = lv_label_create(testSwitch, NULL); //create a labe with the parent object being the switch
  lv_label_set_text(switchLabel, "SWITCH");//sets the text of our label
}

void Display::createBackground(void)
{
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

void Display::createHomeScreen(void)
{
    lv_theme_t *th = lv_theme_alien_init(60, NULL); //60 For TTYellow
    lv_tabview_set_sliding(auto_op_tab, false);
    lv_tabview_set_anim_time(tabs, 0);
//    imageTest2();
    imageTest();
    createOpLEDs();
    createGauge();
    createAutoSelector();
}

void Display::refresh(void)
{
  lv_gauge_set_value(gyroGauge, 0, gyro.get_value());
  if(button.get_value()){lv_led_on(frontLED);}
  else{lv_led_off(frontLED);}
  if(testMotor.get_actual_velocity() > 550){lv_led_on(fwLED);}
  else{lv_led_off(fwLED);}
  if(LightSensor.get_value() < 2700){lv_led_on(backLED);}
  else{lv_led_off(backLED);}
}
