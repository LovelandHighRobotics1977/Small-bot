// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void Robot::RobotInit() {
  Drive(0,0);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  Drive(0,0);
  //reseting and starting timer from zero every time autonomous is run
  timer.Reset();
  timer.Start();
}
void Robot::AutonomousPeriodic() {
  std::cout<<"Starting Autonomous Routine"<<std::endl;

  std::cout<<"Autonomous Routine Complete"<<std::endl;
}

void Robot::TeleopInit() {
  Drive(0,0);
}
void Robot::TeleopPeriodic() {
  //calling drive with xbox stick input
  Drive(-m_driverController.GetLeftY(),m_driverController.GetRightY());
}

void Robot::DisabledInit() {
  Drive(0,0);
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::Drive(float left, float right){
  //setting motor speeds to parameters
  m_l1.Set(left);
  m_l2.Set(left);
  m_r1.Set(right);
  m_r2.Set(right); 
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif