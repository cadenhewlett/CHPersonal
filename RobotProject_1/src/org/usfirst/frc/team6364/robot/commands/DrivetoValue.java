package org.usfirst.frc.team6364.robot.commands;

import org.usfirst.frc.team6364.robot.Robot;
import org.usfirst.frc.team6364.robot.RobotMap;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class DrivetoValue extends Command {

	double CurrentValue;
	boolean Finished;
	boolean OutOfRange;
	boolean inError;
	int count;   
	int Value;

	public DrivetoValue(int value) {
		requires(Robot.drivebase);
		Value = value;
	}

	protected void initialize() {
		Robot.drivebase.DriveTo(Value);
	}

	protected void execute() {
		
	}

	@Override
	protected boolean isFinished() {

		return Finished;
	}

	@Override
	protected void interrupted() {

		end();
	}

	protected void end() {
		
	}
}
