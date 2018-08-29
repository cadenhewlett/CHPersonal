package org.usfirst.frc.team6364.robot.subsystems;

import org.usfirst.frc.team6364.robot.Robot;
import org.usfirst.frc.team6364.robot.RobotMap;
import org.usfirst.frc.team6364.robot.commands.TankDrive;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kauailabs.navx.frc.AHRS;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.SPI;
//import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class Drive extends Subsystem implements PIDOutput {
	public TalonSRX MotorLeft;
	public TalonSRX MotorLeftFollower;
	public TalonSRX MotorRight;
	public TalonSRX MotorRightFollower;
	private final AHRS ahrs;
	public final PIDController DrivePID;

	public int DriveValues[] = new int[3];
	public double Gyro = 0;
	public float Temp = 0;
	public String DriveKeys[] = new String[3];

	public double P;
	public double I;
	public double D;
	public double F;

	public Drive() {
		MotorLeft = new TalonSRX(RobotMap.MOTOR_L.value);
		MotorRight = new TalonSRX(RobotMap.MOTOR_R.value);
		MotorLeftFollower = new TalonSRX(RobotMap.MOTOR_LF.value);
		MotorRightFollower = new TalonSRX(RobotMap.MOTOR_RF.value);
		ahrs = new AHRS(SPI.Port.kMXP);
		DriveKeys[0] = "Left Drive Base";
		DriveKeys[1] = "Right Drive Base";
		DriveKeys[2] = "Left Drive Follower";
		DriveKeys[3] = "Right Drive Follower";
		Robot.initTalon(MotorLeft, false);
		Robot.initTalon(MotorRight, false);
		Robot.initTalon(MotorLeftFollower, true);
		Robot.initTalon(MotorRightFollower, true);

		MotorLeftFollower.follow(MotorLeft);
		MotorRightFollower.follow(MotorRight);

		MotorRight.setInverted(false);
		MotorLeft.setInverted(false);
		MotorLeftFollower.setInverted(false);
		MotorRightFollower.setInverted(false);

		DrivePID = new PIDController(P, I, D, ahrs, this);
		DrivePID.setSubsystem("Drive");
		DrivePID.setInputRange(-180.0f, 180.0f);
		DrivePID.setOutputRange(-0.45, 0.45);
		DrivePID.setAbsoluteTolerance(2.0f);
		DrivePID.setContinuous();
	}

	public void setDrive(ControlMode mode, double LeftVal, double RightVal) {
		MotorRight.set(mode, RightVal);
		MotorLeft.set(mode, LeftVal);
	}

	protected void initDefaultCommand() {
		setDefaultCommand(new TankDrive());

	}

	public void TurnAngle(double angle) {
		ahrs.reset();
		DrivePID.reset();
		DrivePID.setPID(P, I, D);
		DrivePID.setSetpoint(angle);
		DrivePID.setContinuous();

	}
          
	public void DriveTo(int TargetValue) {

		int CurrentValue = (MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_L.value)
				+ MotorRight.getSelectedSensorPosition(RobotMap.MOTOR_R.value)) / 2;
		boolean OutOfRange = /*Math.abs*/((TargetValue - CurrentValue)) > 0;
		if (OutOfRange) {
			MotorLeft.set(ControlMode.PercentOutput, 0.5);
			MotorRight.set(ControlMode.PercentOutput, 0.5);
		}
	}

	public void pidWrite(double output) {
		setDrive(ControlMode.PercentOutput, output, output);
	}

	public double GetGyro() {
		Gyro = ahrs.getAngle();
		return Gyro;
	}

	public void GetTemp() {
		Temp = ahrs.getTempC();
	}

	/* GETS SENSOR VALUE BASED ON STRING INPUT AND TALON INFO */
	public double GetDriveValue(String Type, TalonSRX Talon, int ID) {
		Type = Type.toUpperCase();
		switch (Type) {
		case "PERCENT":
			return Talon.getMotorOutputPercent();
		case "VOLTAGE":
			return Talon.getMotorOutputVoltage();
		case "POSITION":
			return Talon.getSelectedSensorPosition(ID);
		case "VELOCITY":
			return Talon.getSelectedSensorPosition(ID);
		default:
			return 0.0;

		}
	}

	public int[] GetDriveValues(String Type) {
		Type = Type.toUpperCase();
		switch (Type) {
		case "PERCENT":
			DriveValues[0] = (int) (MotorLeft.getMotorOutputPercent());
			DriveValues[1] = (int) (MotorRight.getMotorOutputPercent());
			DriveValues[2] = (int) (MotorLeftFollower.getMotorOutputPercent());
			DriveValues[3] = (int) (MotorRightFollower.getMotorOutputPercent());
			return DriveValues;
		case "VOLTAGE":
			DriveValues[0] = (int) (MotorLeft.getMotorOutputVoltage());
			DriveValues[1] = (int) (MotorRight.getMotorOutputVoltage());
			DriveValues[2] = (int) (MotorLeftFollower.getMotorOutputPercent());
			DriveValues[3] = (int) (MotorRightFollower.getMotorOutputPercent());
			return DriveValues;
		case "POSITION":
			DriveValues[0] = (int) (MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_L.value));
			DriveValues[1] = (int) (MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_R.value));
			DriveValues[2] = (int) (MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_LF.value));
			DriveValues[3] = (int) (MotorLeft.getSelectedSensorPosition(RobotMap.MOTOR_RF.value));
			return DriveValues;
		default:
			DriveValues[0] = DriveValues[0];
			DriveValues[1] = DriveValues[1];
			DriveValues[2] = DriveValues[2];
			DriveValues[3] = DriveValues[3];
			return DriveValues;
		}
	}

}
