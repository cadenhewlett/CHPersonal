package org.usfirst.frc.team6364.robot.subsystems;

import org.usfirst.frc.team6364.robot.Robot;
import org.usfirst.frc.team6364.robot.RobotMap;
import org.usfirst.frc.team6364.robot.commands.TankDrive;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;

//import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;

public class Drive extends Subsystem {
	private TalonSRX MotorLeft;
	private TalonSRX MotorLeftFollower;
	private TalonSRX MotorRight;
	private TalonSRX MotorRightFollower;
	
	public Drive() {
		MotorLeft = new TalonSRX(RobotMap.MOTOR_L.value);
		MotorRight = new TalonSRX(RobotMap.MOTOR_R.value);
		MotorLeftFollower = new TalonSRX(RobotMap.MOTOR_LF.value);
		MotorRightFollower = new TalonSRX(RobotMap.MOTOR_RF.value);
		
		Robot.initTalon(MotorLeft, false);
		Robot.initTalon(MotorRight, false);
		Robot.initTalon(MotorLeftFollower, true);
		Robot.initTalon(MotorRightFollower, true);
		
		MotorLeftFollower.follow(MotorLeft);
		MotorRightFollower.follow(MotorRight);
		
	}
	
	public void setDrive(ControlMode mode, double LeftVal, double RightVal) {
		MotorRight.set(mode, RightVal);
		MotorLeft.set(mode, LeftVal);
	}
	

	protected void initDefaultCommand() {
		setDefaultCommand(new TankDrive());
		
	}

	public double[] SendDriveValues(String Type) {
		Type = Type.toUpperCase();
		double DriveValues[] = new double[1];
		if (Type.equals("PERCENT") || (Type.equals("%"))) {
			DriveValues[0] = MotorLeft.getMotorOutputPercent();
			DriveValues[1] = MotorRight.getMotorOutputPercent();
		} else if (Type.equals("VOLTAGE")||(Type.equals("V"))) {
			DriveValues[0] = MotorLeft.getMotorOutputVoltage();
			DriveValues[1] = MotorRight.getMotorOutputVoltage();
		} else if (Type.equals("POSITION")|| (Type.equals("POS"))) {
			DriveValues[0] = MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_L.value);
			DriveValues[1] = MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_R.value);
		} else {
			DriveValues[0] = 0;
			DriveValues[1] = 0;
		}
		return DriveValues;
	}

}
