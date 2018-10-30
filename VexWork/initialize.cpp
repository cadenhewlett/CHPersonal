#include "main.h"
#include "flywheel.h"
#include "lcd.h"
using namespace okapi;

/*void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(5, "I was pressed!");
	} else {
		pros::lcd::clear_line(5);
	}
}*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
//printf("Battery Level: %d", int(pros::battery::get_capacity()));
//int currentAuto = 0;
pros::Task FW_Task(
	 		FW_Task_fn,
	 		(void*)"PROS",
	 		TASK_PRIORITY_DEFAULT,
	 		TASK_STACK_DEPTH_DEFAULT,
	 		"Flywheel Task"
	 	);
pros::Task LCD_Task(
			LCD_Task_fn,
			(void*)"PROS",
			TASK_PRIORITY_DEFAULT,
			TASK_STACK_DEPTH_DEFAULT,
			"LCD Task"
		);
//	pros::lcd::initialize();
	//pros::lcd::set_text(1, "Hello PROS User!");

//	pros::lcd::register_btn1_cb(on_center_button);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
//	printf("Controller Battery: %d", controller.getBatteryLevel());
	printf("System Battery: %d", pros::battery::get_voltage());
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
