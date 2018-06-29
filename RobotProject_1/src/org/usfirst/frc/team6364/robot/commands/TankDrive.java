package org.usfirst.frc.team6364.robot.commands;

import org.usfirst.frc.team6364.robot.Robot;
import org.usfirst.frc.team6364.robot.subsystems.Drive;

import com.ctre.phoenix.motorcontrol.ControlMode;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class TankDrive extends Command {
	public TankDrive() {
		requires(Robot.drivebase);

	}

	@Override
	protected void initialize() {

	}

	protected void execute() {
		SmartDashboard.putBoolean("Drive Operational", true);
		SmartDashboard.putNumberArray("Drive Values", Robot.drivebase.SendDriveValues("%"));
		SmartDashboard.getBoolean("Drive Operational", false);

		double throttle = (1.0 - Robot.m_oi.JoyLeft.getThrottle()) / -2.0;

		Robot.drivebase.setDrive(ControlMode.PercentOutput, Robot.m_oi.getLeftJoyY() * throttle,
				Robot.m_oi.getRightJoyY() * throttle);

	}

	@Override
	protected boolean isFinished() {
		SmartDashboard.putBoolean("Drive Operational", false);
		return false;
	}

	@Override
	protected void interrupted() {
		SmartDashboard.putBoolean("Drive Operational", false);
		end();
	}
}
