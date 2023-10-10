// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {

	frc::SmartDashboard::PutString("Match State","   Disabled");
	frc::SmartDashboard::PutString("Robot Name",Swordtip::Misc::Robot_Name);

	frc::SmartDashboard::PutNumber("X_POS", 0);
	frc::SmartDashboard::PutNumber("Y_POS", 0);

	frc::SmartDashboard::PutNumber("X_VEL", 0);
	frc::SmartDashboard::PutNumber("Y_VEL", 0);

	m_swerve.Drive(0_fps,0_fps,0_deg_per_s,0,Swordtip::Frame::RotationPoints::Center);
	m_cubeArm.SetIntake(0,0);
	m_cubeArm.SetAngle(0,0);
	m_cubeArm.SetSpeed(0,0,0);

	timer.Start();

	/*
	r_driveCam = frc::CameraServer::StartAutomaticCapture(0);
	r_armCam = frc::CameraServer::StartAutomaticCapture(1);

	r_driveCam.SetPixelFormat(cs::VideoMode::PixelFormat::kYUYV);
	r_armCam.SetPixelFormat(cs::VideoMode::PixelFormat::kYUYV);
	*/
}
void Robot::RobotPeriodic() {

	robot_position = m_swerve.UpdateOdometry();

}

void Robot::AutonomousInit() {

	frc::SmartDashboard::PutString("Match State","   Autonomous");

	m_swerve.Drive(0_mps,0_mps,0_deg_per_s,0,Swordtip::Frame::RotationPoints::Center);
	m_swerve.SetNeutralMode(Brake);
	
	timer.Restart();

	gyro->Reset();

}
void Robot::AutonomousPeriodic() {

	current_time = std::ceil(timer.Get().value());

	// Set autonomous stage based on time elapsed
	switch (current_time){
		case 1: auto_stage = 1; break;
		case 2: auto_stage = 2; break;
		case 3: auto_stage = 3; break;
		case 4: auto_stage = 4; break;
		case 5: auto_stage = 5; break;
		default: auto_stage = 5; break;
	}
	switch(autoCase)
	{
		case 1://right station
			switch (auto_stage){
				case 1: 
					// Fire a cube into the mid node
					m_cubeArm.SetSpeed(0,1,0);
					m_cubeArm.SetIntake(0,1);
					break;

				case 2: 
					// Stop the intake and drive quickly away going slightly to the right
					m_cubeArm.SetIntake(0,0);
					m_swerve.Drive(Swordtip::Velocity::Maximums::Max_Speed,3_fps,0_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					break;

				case 3: 
					// Drive to the left to approach the charge station from behind
					m_swerve.Drive(0_mps,0_mps,-90_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					break;

				case 4:
					// Auto Balance the robot
					m_swerve.Drive( 0_fps, -Swordtip::Velocity::Maximums::Max_Speed, 0_deg_per_s, 0.3, Swordtip::Frame::RotationPoints::Center);
			
				break;
				case 5:
					m_swerve.AutoBalance();
				break;

				default:
					// Freeze the robot if not in any stage
					m_swerve.HaltRobot();
					break;

				}
		break;
		case 2://mid station
			switch (auto_stage){
				case 1: 
					// Fire a cube into the mid node
					m_cubeArm.SetSpeed(0,1,0);
					m_cubeArm.SetIntake(0,1);
					break;

				case 2: 
					// Stop the intake and drive quickly away 
					m_cubeArm.SetIntake(0,0);
					m_swerve.Drive(5_fps,0_fps,0_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					break;

				case 3: 
					//auto balance
					m_swerve.AutoBalance();
					break;
			break;

			default:
				// Freeze the robot if not in any stage
				m_swerve.HaltRobot();
				break;

		}
		break;
		case 3://left station
			switch (auto_stage){
				case 1: 
					// Fire a cube into the mid node
					m_cubeArm.SetSpeed(0,1,0);
					m_cubeArm.SetIntake(0,1);
					break;

				case 2: 
					// Stop the intake and drive quickly away moving ever so slightly to the left to avoid the ramp
					m_cubeArm.SetIntake(0,0);
					m_swerve.Drive(5_fps,0.5_fps,0_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					break;

				case 3: 
					//turn to pick up cube and put the arm down
					m_swerve.Drive(0_fps,0_fps,90_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					m_cubeArm.SetAngle(false, true);
					m_cubeArm.SetIntake(true, false);					
					break;
				case 4:
				//pick up cube
					m_swerve.Drive(5_fps,0_fps,0_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					m_cubeArm.SetIntake(false, false);
					m_cubeArm.SetAngle(true, false);
					break;
				case 5:
				//drive onto platform and balance
					m_swerve.Drive(-5_fps,0_fps,-90_deg_per_s,1,Swordtip::Frame::RotationPoints::Center);
					m_swerve.AutoBalance();
					break;
				
			break;

			default:
				// Freeze the robot if not in any stage
				m_swerve.HaltRobot();
				break;

		}
		break;
		default:
			m_swerve.HaltRobot();
		break;
	};
	// Autonomous stages
	
}

void Robot::TeleopInit() {

	frc::SmartDashboard::PutString("Match State","   TeleOperated");

	m_swerve.SetNeutralMode(Brake);
	
	gyro->Reset();

}

void Robot::TeleopPeriodic() {

	driver.update();
	shooter.update();

	// Reset Gyro
	if(driver.gyro_reset){
		gyro->Reset();
	}

	// Control mechanism
	m_cubeArm.SetAngle(shooter.angle_up, shooter.angle_down);
	m_cubeArm.SetIntake(shooter.intake_in, shooter.intake_out);
	m_cubeArm.SetSpeed(shooter.speed_slow, shooter.speed_medium, shooter.speed_fast);
	
	// Select rotation speed from triggers
	switch ((driver.trigger_one + driver.trigger_two)){
	case 0:
		center_of_rotation = Swordtip::Frame::RotationPoints::Center;
		rotation_speed = Swordtip::Velocity::Rotation::Slow;
		break;
	
	case 1:
		center_of_rotation = Swordtip::Frame::RotationPoints::Center;
		rotation_speed = Swordtip::Velocity::Rotation::Medium;
		break;

	case 2:
		center_of_rotation = Swordtip::Frame::RotationPoints::Center;
		rotation_speed = Swordtip::Velocity::Rotation::Fast;
		break;
	}

	forward = (-m_forwardLimiter.Calculate(frc::ApplyDeadband(driver.forward, 0.2)) * driver.throttle) * Swordtip::Velocity::Maximums::Max_Speed;
	strafe = (-m_strafeLimiter.Calculate(frc::ApplyDeadband(driver.strafe, 0.2)) * driver.throttle) * Swordtip::Velocity::Maximums::Max_Speed;
	rotate = (-m_rotateLimiter.Calculate(frc::ApplyDeadband(driver.rotate, 0.3)) * sqrt(driver.throttle)) * rotation_speed;

	// Drive the swerve modules
	if(driver.emergency_stop){
		// Emergency braking (Button 5)
		m_swerve.HaltRobot();
	}else{
		// Normal Drive
		m_swerve.Drive(forward, strafe, rotate, driver.field_oriented, center_of_rotation);
	}

	std::cout<<rotate.value()<<std::endl;

	// Put values to SmartDashboard
	frc::SmartDashboard::PutNumber("throttle", driver.throttle);
	
	frc::SmartDashboard::PutNumber("Angle", static_cast<int>(gyro->GetYaw()));
	frc::SmartDashboard::PutNumber("X_POS", robot_position.X().value());
	frc::SmartDashboard::PutNumber("Y_POS", robot_position.Y().value());

	frc::SmartDashboard::PutNumber("R_VEL", (double) rotate);
	frc::SmartDashboard::PutNumber("X_VEL", gyro->GetVelocityX());
	frc::SmartDashboard::PutNumber("Y_VEL", gyro->GetVelocityY());
}

void Robot::DisabledInit() {
	frc::SmartDashboard::PutString("Match State","   Disabled");
	m_swerve.HaltRobot();
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {
	frc::SmartDashboard::PutString("Match State","   Test");
}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRc_TESTS
int main() {
	return frc::StartRobot<Robot>();
}
#endif