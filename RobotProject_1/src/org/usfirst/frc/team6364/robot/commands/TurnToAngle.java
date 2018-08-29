package org.usfirst.frc.team6364.robot.commands;

import org.usfirst.frc.team6364.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class TurnToAngle extends Command {

	public enum RobotState{
		DISABLED, TELEOP, AUTONOMOUS
	}
	double Angle;
	boolean Finished;
	boolean inError;
	int count;
	public TurnToAngle(double angle) {
		requires(Robot.drivebase);
		Angle = angle;
	}
	protected void initialize() {
		Robot.drivebase.TurnAngle(Angle);
	}

	protected void execute() {
		double error = Robot.drivebase.DrivePID.getError();
		double errorDif = error -(Robot.drivebase.DrivePID.getSetpoint());
		//SmartDashboard.putNumber("Auto Drive Values", Robot.drivebase.GetDriveValues("Percent"));
		SmartDashboard.putNumber("Drive Error Diff", errorDif);
		SmartDashboard.putNumber("Drive Error", error);
		if(Math.abs(error)<2) {
			count++;
			Finished = count >= 5;	
		}
		else {
			count = 0;
		}
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
		Robot.drivebase.DrivePID.disable();
	}
}
