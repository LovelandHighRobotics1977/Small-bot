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
  case 1:
    m_intake.Set(-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_intake.Set(0);
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Drive(driveSpeed, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    Drive(-driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Drive(driveSpeed, driveSpeed, false);
    m_angle.Set(-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_angle.Set(0);
    Drive(driveSpeed, driveSpeed + 0.2, false);
    m_intake.Set(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    m_intake.Set(0);
    m_angle.Set(1);
    Drive(0, 0, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    m_angle.Set(0);
    driveSpeed = 0.25;
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    Drive(-driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    Drive(driveSpeed, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m_intake.Set(-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    m_intake.Set(0);
    break;

    //--------------------------------------------------------
    //--------------------------------------------------------
    //--------------------------------------------------------

  case 2:
    // middle
    driveSpeed = -0.4;
    m_intake.Set(0);
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    m_intake.Set(1);
    Drive(driveSpeed + 0.07, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Drive(driveSpeed, driveSpeed + 0.07, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    m_intake.Set(0);
    Drive(-driveSpeed - 0.07, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Drive(-driveSpeed, -driveSpeed - 0.07, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Drive(-driveSpeed, -driveSpeed, false);

    std::this_thread::sleep_for(std::chrono::milliseconds(25000));

    m_angle.Set(-1);

    break;

    //------------------------------------------------------
    //-----------------------------------------\_/----------
    //--------------------lala------------------------------

  case 3:
    // right
    driveSpeed = -0.25;
    m_intake.Set(-1); // out
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    m_intake.Set(0); // ok stop
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // probably crashed by now
    m_angle.Set(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // arm down and also go
    m_angle.Set(0);
    Drive(driveSpeed, driveSpeed + 0.05, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 90 degree turn and stop down
    m_intake.Set(0.6);
    Drive(driveSpeed * 0.5, driveSpeed * 0.5, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // eat cube maybe and go slow
    Drive(0, 0, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // stop
    m_intake.Set(0);
    m_angle.Set(-1);
    Drive(-driveSpeed, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); // reverse and arm up
    Drive(driveSpeed, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    m_angle.Set(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 90 degree turn
    Drive(driveSpeed, driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // go to drive station
    Drive(-driveSpeed, -driveSpeed, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // 180 ?
    Drive(0, 0, true);
    break;
  default:
    std::cout << "idiot";
    break;
  }
}
void Robot::AutonomousPeriodic()
{
  std::cout << "Starting Autonomous Routine" << std::endl;
  std::cout << "Autonomous Routine Complete" << std::endl;
}

void Robot::TeleopInit() { Drive(0, 0, true); }
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
    Robot::armspeed = 0.6;
  }
  else if (m_xBox.GetYButtonPressed())
  {
    Robot::armspeed = 1;
  }
  float armAngle = ((m_xBox.GetRawAxis(2) + 1) / 2) - ((m_xBox.GetRawAxis(3) + 1) / 2);
  if (armAngle > 0 && m_LowerSwitch.Get() == false)
  {
    m_angle.Set(1);
  }
  else if (armAngle < 0 && m_UpperSwitch.Get() == false)
  {
    m_angle.Set(-1);
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
    m_intake.Set(0.6);
    // std::cout << "intake out";
  }
  else
  {
    m_intake.Set(0);
  }
}

void Robot::Drive(float left, float right, bool stop)
{
  // setting motor speeds to parameters
  left *= -(((-m_joystick.GetRawAxis(4)) + 1) / 2) -
          (0.01 * (0.9 - m_joystick.GetRawAxis(4)));
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

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif