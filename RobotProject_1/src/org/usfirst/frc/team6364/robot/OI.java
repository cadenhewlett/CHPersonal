/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team6364.robot;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.JoystickButton;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
	
	public static final int LEFT_HZ_AXIS = 0;
	public static final int LEFT_VT_AXIS = 1;
	public static final int LEFT_Z_AXIS = 3;
	public static final int RIGHT_HZ_AXIS = 4;
	public static final int RIGHT_VT_AXIS = 5;
	public static final int RIGHT_Z_AXIS = 2;
	public static final double deadZone = 0.1;
	

	public final Joystick DriverJoystick = new Joystick(RobotMap.JoyL.value);
	public final Button button = new JoystickButton(DriverJoystick, 2);
	
	public final Joystick JoyRight = new Joystick(RobotMap.JoyR.value);
	
	public double getLeftJoyX() {
		double raw = DriverJoystick.getX();
		return Math.abs(raw) < deadZone ? 0.0 : raw;

	}

	public double getLeftJoyY() {
		double raw = DriverJoystick.getY();
		return Math.abs(raw) < deadZone ? 0.0 : raw;

	}

	public double getRightJoyX() {
		double raw = JoyRight.getX();
		return Math.abs(raw) < deadZone ? 0.0 : raw;

	}

	public double getRightJoyY() {
		double raw = JoyRight.getY();
		return Math.abs(raw) < deadZone ? 0.0 : raw;

	}
	public OI(){
	
	}
	//// CREATING BUTTONS
	// One type of button is a joystick button which is any button on a
	//// joystick.
	// You create one by telling it which joystick it's on and which button
	// number it is.
	// Joystick stick = new Joystick(port);
	// Button button = new JoystickButton(stick, buttonNumber);

	// There are a few additional built in buttons you can use. Additionally,
	// by subclassing Button you can create custom triggers and bind those to
	// commands the same as any other Button.

	//// TRIGGERING COMMANDS WITH BUTTONS
	// Once you have a button, it's trivial to bind it to a button in one of
	// three ways:

	// Start the command when the button is pressed and let it run the command
	// until it is finished as determined by it's isFinished method.
	// button.whenPressed(new ExampleCommand());

	// Run the command while the button is being held down and interrupt it once
	// the button is released.
	// button.whileHeld(new ExampleCommand());

	// Start the command when the button is released and let it run the command
	// until it is finished as determined by it's isFinished method.
	// button.whenReleased(new ExampleCommand());
}
