// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/XboxController.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with arcade steering.
 */
class Robot : public frc::TimedRobot {
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_leftMotor1{2};
  ctre::phoenix::motorcontrol::can::WPI_VictorSPX m_leftMotor2{5};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_rightMotor1{6};
  ctre::phoenix::motorcontrol::can::WPI_TalonSRX m_rightMotor2{3};

  frc::XboxController pilot {0};




  frc::SpeedControllerGroup leftGroup{m_leftMotor1, m_leftMotor2};
  frc::SpeedControllerGroup rightGroup{m_rightMotor1, m_rightMotor2};
  frc::DifferentialDrive m_robotDrive{leftGroup, rightGroup};
  frc::Joystick m_stick{0};

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
  
    m_leftMotor1.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_leftMotor2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_rightMotor1.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
    m_rightMotor2.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);

    m_rightMotor1.SetInverted(false);
    m_rightMotor2.SetInverted(false);
    m_leftMotor1.SetInverted(true);
    m_leftMotor2.SetInverted(true);
  }

  void TeleopPeriodic() override {
    // Drive with arcade style
    m_robotDrive.ArcadeDrive(pilot.GetRightY(), -pilot.GetLeftX() * 0.8);
  }
}; 

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
