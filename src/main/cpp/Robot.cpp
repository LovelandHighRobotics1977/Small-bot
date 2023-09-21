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
  armTime.Reset();
  armTime.Start();
  double driveSpeed = -0.3;
  m_intake.Set(-1);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  m_intake.Set(0);
  Drive(driveSpeed, driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_angle.Set(-0.6);
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  m_angle.Set(0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  m_intake.Set(1);
  Drive(driveSpeed, driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_intake.Set(0);
  m_angle.Set(1);
  Drive(-driveSpeed, -driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  m_angle.Set(0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_intake.Set(-1);
  Drive(0, 0, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_intake.Set(0);
  /*Drive(driveSpeed, driveSpeed, false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Drive(0, 0, true);
  */


}
void Robot::AutonomousPeriodic() {
  std::cout<<"Starting Autonomous Routine"<<std::endl;
  std::cout<<"Autonomous Routine Complete"<<std::endl;
}

void Robot::TeleopInit() {
  Drive(0,0,true);
}
void Robot::TeleopPeriodic() {
  Direction();
  armTime.Reset();
  Arm();
}

void Robot::DisabledInit() {
  Drive(0,0,true);
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::Direction()
{
  float forward = m_joystick.GetY();
  float rotation = m_joystick.GetX();
  if(!m_joystick.GetRawButton(2))
  {
    rotation /= 1.5;
  }
  if(m_joystick.GetRawButton(3))
  {
    rotation *= 2;
  }
  //std::cout << "left motor " << forward-rotation << "\nright motor " << forward + rotation << "\n";
  if(forward > 0.2 || forward < -0.2 || rotation > 0.2 || rotation < -0.2)
  {
    Drive(forward - rotation, forward + rotation, false);
  }
  else
  {
    Drive(0, 0, false);
  }
  
}
void Robot::Arm()
{
  //std::cout << m_joystick.GetRawAxis(4) << std::endl; 
    //std::cout << "enterd arm up\n"; 
      if(m_UpperSwitch.Get() == 0 && armTime.AdvanceIfElapsed(units::second_t(0.5)) && m_joystick.GetRawButton(6))
      {
        m_angle.Set(1);
        std::cout << "arm up\n";
      }
      else if(m_LowerSwitch.Get() == 0 && armTime.AdvanceIfElapsed(units::second_t(0.5)) && m_joystick.GetRawButton(6))
      {
        m_angle.Set(-1);
        std::cout << "arm down\n";
      }
  if (m_joystick.GetRawButton(1))
  {
    m_intake.Set(-1);
    //std::cout << "intake in\n";
  }
  else if(m_joystick.GetRawButton(7))
  {
    m_intake.Set(0.6);
    //std::cout << "intake out";
  }
  else
  {
    m_intake.Set(0);
  }
}

void Robot::Drive(float left, float right, bool stop){
  //setting motor speeds to parameters
  left *= -(((-m_joystick.GetRawAxis(4)) + 1) / 2) - (0.09 *((1-m_joystick.GetRawAxis(4))));
  right *= (((-m_joystick.GetRawAxis(4)) + 1)/2);
  //if (m_pdp.GetCurrent(14) < 10 && m_pdp.GetCurrent(15) < 10 && m_pdp.GetCurrent(16) < 10 && m_pdp.GetCurrent(17) < 10)
  {
    m_l1.Set(left);
    m_l2.Set(left);
    m_r1.Set(right);
    m_r2.Set(right); 
  }
  /*
  else 
  {
    m_l1.Set(0);
    m_l2.Set(0);
    m_r1.Set(0);
    m_r2.Set(0); 
  }
  */
  

  if(left == 0 && right == 0){
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