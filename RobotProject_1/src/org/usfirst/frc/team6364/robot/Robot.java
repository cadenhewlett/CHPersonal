/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package org.usfirst.frc.team6364.robot;

import java.util.HashMap;
import java.util.Map;

import org.usfirst.frc.team6364.robot.subsystems.*;

import com.ctre.phoenix.motorcontrol.LimitSwitchNormal;
import com.ctre.phoenix.motorcontrol.LimitSwitchSource;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kauailabs.navx.frc.*;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Robot extends TimedRobot {
	AHRS ahrs;
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
		// autoSelector.addDefault("No Autonomous Selected", new None());
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
		Scheduler.getInstance().run();
		SmartDashboard.putNumber("Drive Motor Left",
				Robot.drivebase.GetDriveValue("POSITION", Robot.drivebase.MotorLeft, RobotMap.MOTOR_L.value));
		InsertionSort(Robot.drivebase.DriveKeys, (Robot.drivebase.GetDriveValues("PERCENT")));
		SmartDashboard.putNumber("Gyro", Robot.drivebase.GetGyro());

	}

	/**
	 * This function is called periodically during test mode.
	 */
	@Override
	public void testPeriodic() {
		SmartDashboard.putData("Move Base", new Drive());
		SmartDashboard.putData(Robot.drivebase);
	}

	public static void initTalon(TalonSRX motor, Boolean isInverted) {
		motor.setNeutralMode(NeutralMode.Coast);
		motor.neutralOutput();
		motor.setSensorPhase(false);

		motor.configForwardLimitSwitchSource(LimitSwitchSource.FeedbackConnector, LimitSwitchNormal.NormallyOpen, 0);
		motor.configReverseLimitSwitchSource(LimitSwitchSource.FeedbackConnector, LimitSwitchNormal.NormallyOpen, 0);

		motor.configNominalOutputForward(0.0, 0);
		motor.configNominalOutputReverse(0.0, 0);
		motor.configClosedloopRamp(0.5, 0);

		motor.setInverted(isInverted);
	}

	public static double Feet_to_Encoder(double Input) {
		return (Input / 1.57) * 4096;
	}

	public static void InsertionSort(String[] Key, int[] Value) {
		if ((Key.length - Value.length) == 0) {
			HashMap hashMap = new HashMap();
			Map<Integer, String> dictionaryKeys = hashMap; // new map with inverted keys/values
			int j, temp;

			for (int i = 1; i < (Key.length + 1); i++) {
				dictionaryKeys.put(Value[i - 1], Key[i - 1]);
			}

			for (int i = 1; i < Value.length; i++) // repeats while iteration is less than the length of the array
			{
				j = i - 1; // j is one less than the iteration
				while (j >= 0 && Value[j] < Value[i])// while j is greater than 0, and the jth term of the array is
														// greater than
				// the
				// ith term of the array
				{
					temp = Value[i]; // temp becomes ith term
					Value[i] = Value[j];// ith term become jth term
					Value[j] = temp;// jth term becomes temp

					Key[i] = Key[j]; // ith term becomes jth term
					Key[j] = dictionaryKeys.get(temp); // jth term becomes the dictionary reference with the
														// corresponding integer value

					i = j;
					j--; // decrement loop

				}
			}
			// for testing
			// System.out.println(Arrays.toString(a)); // prints the array
			// System.out.println(Arrays.toString(b));
			// System.out.println(String.format("%s, %s", b[], a[]));

		}
	}// end sort
}
