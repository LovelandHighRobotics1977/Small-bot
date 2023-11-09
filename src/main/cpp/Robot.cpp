// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"


void Robot::RobotInit()
{
  Drive(0, 0, true);
  m_intake.SetNeutralMode(Coast);
  m_angle.SetNeutralMode(Brake);
  m_l1.SetNeutralMode(Coast);
  m_l2.SetNeutralMode(Coast);
  m_r1.SetNeutralMode(Coast);
  m_r2.SetNeutralMode(Coast);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  Drive(0, 0, true);
  // reseting and starting timer from zero every time autonomous is run
  timer.Reset();
  timer.Start();
  armTime.Reset();
  armTime.Start();
  double driveSpeed = -0.25;
  switch (Robot::atonMode)
  {
  case 0:
  driveFor(10, 0.25);

  break;
  case 1:
    scoreAuto();
    driveFor(2, 0.4);
    turnFor(22.5, 0.25, 'r');
    driveFor(4, 0.4);
    turnFor(20, 0.25, 'l');
    driveFor(12, 0.4);
  break;

    //--------------------------------------------------------
    //--------------------------------------------------------
    //--------------------------------------------------------

  case 2:
    // middle
   driveSpeed = 0.6;
   scoreAuto();
    forwardFunction();
    m_angle.Set(1);
    break;

  case 3:
    // right
    scoreAuto();
    driveFor(1, 0.25);
    turnFor(22.5, 0.25, 'l');
    driveFor(4.5, 0.25);
    turnFor(24, 0.25, 'r');
    driveFor(12, 0.25);
    break;
  default:
    std::cout << "idiot";

  std::cout << "sending drive";
  driveFor(10, 0.25);

    break;
  }
}
void Robot::AutonomousPeriodic()
{
  /*
  std::cout << "Starting Autonomous Routine" << std::endl;
  std::cout << "Autonomous Routine Complete" << std::endl;
  */
}

void Robot::TeleopInit() { Drive(0, 0, true);  armUp = true;}
void Robot::TeleopPeriodic()
{
  Direction();
  armTime.Reset();
  Arm();
}

void Robot::DisabledInit() { Drive(0, 0, false); }
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::Direction()
{
  float forward = m_joystick.GetY();
  float rotation = m_joystick.GetX();
  if (!m_joystick.GetRawButton(2))
  {
    rotation /= 1.5;
  }
  if (m_joystick.GetRawButton(3))
  {
    rotation *= 2;
  }
  // std::cout << "left motor " << forward-rotation << "\nright motor " <<
  // forward + rotation << "\n";
  if (forward > 0.2 || forward < -0.2 || rotation > 0.2 || rotation < -0.2)
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
  if(m_xBox.GetXButtonPressed())
  {
    Robot::armspeed = 0.4;
  }
  else if (m_xBox.GetYButtonPressed())
  {
    Robot::armspeed = 0.6;
  }
  else if(m_xBox.GetBButtonPressed())
  {
    Robot::armspeed = 1;
  }
  if(m_xBox.GetAButtonPressed())
  {
    scoreAuto();
  }
  if ( m_xBox.GetRawAxis(2) >= 0.2 && m_UpperSwitch.Get() == true)
  {
    m_angle.Set(-0.6);
  }
  else if (m_UpperSwitch.Get() == false && m_xBox.GetRawAxis(2) < 0.2 && m_xBox.GetRawAxis(3) < 0.2)
  {
    m_angle.Set(1);
  }
  else
  {
    m_angle.Set(0);
  }
  if (m_xBox.GetRawButton(6))
  {
    m_intake.Set(-Robot::armspeed);
    // std::cout << "intake in\n";
  }
  else if (m_xBox.GetRawButton(5))
  {
    m_intake.Set(0.4);
    // std::cout << "intake out";
  }
  else
  {
    m_intake.Set(0);
  }
}

void Robot::scoreAuto()
{
  m_angle.Set(-1);
  std::this_thread::sleep_for(std::chrono::milliseconds(245));
  m_intake.Set(-1);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  m_angle.Set(1);
  m_intake.Set(0);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  m_angle.Set(0);
}


void Robot::driveFor (int distance, float speed)
{
  int time = fabs(distance * 92 / speed);
  m_l1.SetNeutralMode(Coast);
  m_l2.SetNeutralMode(Coast);
  m_r1.SetNeutralMode(Coast);
  m_r2.SetNeutralMode(Coast);
  m_l1.Set(-speed*0.2);
  m_l2.Set(-speed * 0.2);
  m_r1.Set(speed);
  m_r2.Set(speed);
  std::this_thread::sleep_for(std::chrono::milliseconds(time));
  Drive(0, 0, true);
}

void Robot::turnFor(int degrees, float speed, char direction)
{
  int time = fabs(degrees * (4.77 / speed));
  if (direction == 'r')
  {
    m_l1.Set(speed -
          (0.02 * (1 - speed)));
    m_l2.Set(speed -
          (0.02 * (1 - speed)));
    m_r1.Set(speed);
    m_r2.Set(speed);
  }
  else if (direction == 'l')
  {
    m_l1.Set(-speed);
    m_l2.Set(-speed);
    m_r1.Set(-speed);
    m_r2.Set(-speed);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(time));
  Drive(0, 0, true);
}


void Robot::Drive(float left, float right, bool stop)
{
  // setting motor speeds to parameters
  left *= -(((-m_joystick.GetRawAxis(4)) + 1) / 2) +
           (0.2 * (1 - m_joystick.GetRawAxis(4)));
  right *= (((-m_joystick.GetRawAxis(4)) + 1) / 2);
  // if (m_pdp.GetCurrent(14) < 10 && m_pdp.GetCurrent(15) < 10 &&
  // m_pdp.GetCurrent(16) < 10 && m_pdp.GetCurrent(17) < 10)
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


  if (left == 0 && right == 0)
  {
    m_l1.SetNeutralMode(Brake);
    m_l2.SetNeutralMode(Brake);
    m_r1.SetNeutralMode(Brake);
    m_r2.SetNeutralMode(Brake);
  }
  else
  {
    m_l1.SetNeutralMode(Coast);
    m_l2.SetNeutralMode(Coast);
    m_r1.SetNeutralMode(Coast);
    m_r2.SetNeutralMode(Coast);
  }
}
void Robot::forwardFunction(){
  driveFor(15, 0.65);
  driveFor(6, 0.2);
  //m_intake.Set();
  //m_angle();
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif