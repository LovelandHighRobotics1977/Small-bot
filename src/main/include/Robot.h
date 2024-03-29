// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

//Included with timed robot skeleton
#include <frc/TimedRobot.h>
//Used to interface with xbox controller
#include <frc/XboxController.h>
//used to control talonSRX and falcon500(talonFX)
//must be added as a vendor library improtant
#include <ctre/Phoenix.h>
//output text library
#include <iostream>
//timer library
#include <frc/Timer.h>

#include <frc/DigitalInput.h>
#include <frc/Joystick.h>
#include <frc/PowerDistribution.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;
  //written to control left side and right side independantly with one line
  // Drive(Left side speed (-1 to 1), right side speed (-1 to 1))
  void Drive(float left, float right, bool stop);
  void Direction();
  void Arm();

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void driveFor(int distance, float speed);

  void turnFor(int degrees, float speed, char direction);

  void scoreAuto();

  void forwardFunction();

  int atonMode = 3;
  //1 short, Right Red, Left Blue
  //2 mid
  //3 long, Left Red, Left Blue

  float armspeed = 0.4;
  bool armUp = true;

  private:
  //Declaring xbox contoller
  //frc::XboxController m_driverController{0};
  
  //Declaring motors and establishing CAN IDs 
  //use phoenix tuner to get CAN IDs and put them in the brackets
  WPI_TalonFX m_l1{5};
  WPI_TalonFX m_l2{6};
  WPI_TalonFX m_r1{3};
  WPI_TalonFX m_r2{4};
  //declareing mech motore
  WPI_TalonSRX m_angle{1};
  WPI_TalonSRX m_intake{2};
  //declaring limit switches
  frc::DigitalInput m_LowerSwitch{0};
  frc::DigitalInput m_UpperSwitch{1};
  frc::DigitalInput m_Auto1{2};
  frc::DigitalInput m_Auto2{3};
  frc::DigitalInput m_Auto3{4};
  //declaring inputs
  frc::Joystick m_joystick{1};
  frc::XboxController m_xBox{0};
  //declaring power distabution for current limiting
  frc::PowerDistribution m_pdp{1, frc::PowerDistribution::ModuleType::kRev};  
  //Declaring timer to use for timed events like autonomous
  frc::Timer timer;
  frc::Timer armTime;
};