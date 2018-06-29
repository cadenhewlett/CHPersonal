/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team6364.robot;

import org.usfirst.frc.team6364.robot.subsystems.*;

import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Robot extends TimedRobot {

	public static OI m_oi;
	public static Drive drivebase;
	Command m_autonomousCommand;
	SendableChooser<Command> autoSelector = new SendableChooser<>();

	
	@Override
	public void robotInit() {
		m_oi = new OI();
		drivebase = new Drive();
		// Setting up auto chooser
		autoSelector = new SendableChooser<>();
		//autoSelector.addDefault("No Autonomous Selected", new None());
		// using real autos, of course
		SmartDashboard.putData("Autonomous Mode Selector", autoSelector);

	}

	@Override
	public void disabledInit() {

	}

	@Override
	public void disabledPeriodic() {
		Scheduler.getInstance().run();
	}

	@Override
	public void autonomousInit() {
		m_autonomousCommand = autoSelector.getSelected();
		m_autonomousCommand.start();

		// schedule the autonomous command (example)
	}

	@Override
	public void autonomousPeriodic() {
		Scheduler.getInstance().run();
	}

	@Override
	public void teleopInit() {
		if (m_autonomousCommand != null) {
			m_autonomousCommand.cancel();
		}
	}

	/**
	 * This function is called periodically during operator control.
	 */
	@Override
	public void teleopPeriodic() {
		while(isEnabled()) {
			int counter = 0;
			counter++;
			SmartDashboard.putNumber("Counter", counter);
			Timer.delay(0.10);
		}
		Scheduler.getInstance().run();
	}

	/**
	 * This function is called periodically during test mode.
	 */
	@Override
	public void testPeriodic() {
	}
	
	public static void initTalon(TalonSRX motor, Boolean isInverted) {
		motor.setNeutralMode(NeutralMode.Coast);
		motor.neutralOutput();
		motor.setSensorPhase(false);

		motor.configForwardLimitSwitchSource(LimitSwitchSource.FeedbackConnector, LimitSwitchNormal.NormallyOpen, 0);
		motor.configReverseLimitSwitchSource(LimitSwitchSource.FeedbackConnector, LimitSwitchNormal.NormallyOpen, 0);
		
		motor.configNominalOutputForward(0.0, 0);
		motor.configNominalOutputReverse(0.0, 0);
		motor.configClosedloopRamp(0.5,  0);
		
		motor.setInverted(isInverted);
	}
}
