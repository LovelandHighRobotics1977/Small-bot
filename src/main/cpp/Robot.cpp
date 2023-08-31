// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
  Drive(0,0,true);
  m_intake.SetNeutralMode(Coast);
  m_angle.SetNeutralMode(Brake);
  m_l1.SetNeutralMode(Coast);
  m_l2.SetNeutralMode(Coast);
  m_r1.SetNeutralMode(Coast);
  m_r2.SetNeutralMode(Coast);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  Drive(0,0,true);
  //reseting and starting timer from zero every time autonomous is run
  timer.Reset();
  timer.Start();
  double driveSpeed = 0.3;
  while(-m_LowerSwitch.Get())
  {
    m_angle.Set(1);
  }
  m_angle.Set(0);
  m_intake.Set(1);
  Drive(driveSpeed,driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  Drive(0,0, true);
  m_intake.Set(0);
  while(-m_UpperSwitch.Get())
  {
    m_angle.Set(-1);
  }
  m_angle.Set(0);
  Drive(-driveSpeed, -driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  Drive(0,0, true);
  m_intake.Set(-1);
  Drive(driveSpeed, driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  Drive(0,0, true);
}
void Robot::AutonomousPeriodic() {
  std::cout<<"Starting Autonomous Routine"<<std::endl;

  std::cout<<"Autonomous Routine Complete"<<std::endl;
}

void Robot::TeleopInit() {
  Drive(0,0,true);
}
void Robot::TeleopPeriodic() {
  //calling drive with xbox stick input
  double left_speed = 0.9;
  double right_speed = 1;
  Drive(-m_driverController.GetLeftY()*left_speed,m_driverController.GetRightY()*right_speed,m_driverController.GetAButton());
  m_intake.Set((m_driverController.GetRightBumper() - m_driverController.GetLeftBumper()) * 1);
  m_angle.Set((
    (m_driverController.GetLeftTriggerAxis() * !m_UpperSwitch.Get()) - 
    (m_driverController.GetRightTriggerAxis() * !m_LowerSwitch.Get())
    ) * 1);
}

void Robot::DisabledInit() {
  Drive(0,0,true);
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::Drive(float left, float right, bool stop){
  //setting motor speeds to parameters
  m_l1.Set(left);
  m_l2.Set(left);
  m_r1.Set(right);
  m_r2.Set(right); 

  if(stop){
    m_l1.SetNeutralMode(Brake);
    m_l2.SetNeutralMode(Brake);
    m_r1.SetNeutralMode(Brake);
    m_r2.SetNeutralMode(Brake);
  }else{
    m_l1.SetNeutralMode(Coast);
    m_l2.SetNeutralMode(Coast);
    m_r1.SetNeutralMode(Coast);
    m_r2.SetNeutralMode(Coast);
  }
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif