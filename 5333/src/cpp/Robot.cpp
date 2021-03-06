// Shared headers
#include "curtinfrc/math.h"
#include "curtinfrc/drivetrain.h"
#include "curtinfrc/strategy/mp_strategy.h"
#include "WPILib.h"

// Robot part classes
#include "IO.h"
#include "Belev.h"
#include "Map.h"
#include "Winch.h"
#include "ControlMap.h"
#include "DriveStarategy.h"
#include "Auto.h"

// Other required libraries
#include <string>
#include <SmartDashboard/SmartDashboard.h>
#include <iostream>
#include <stdint.h>
#include <cmath>

using namespace frc; // WPILib classes/functions
using namespace std;

class Robot : public TimedRobot {
public:
  Drivetrain *drive;

  BelevatorControl *belev;
  WinchControl *winch;

  IO *io;

  AutoControl *auto_;

  Robot() { }

  void RobotInit() {
    io = IO::get_instance(); // Refer to IO

    drive = new Drivetrain(io->left_motors[0], io->right_motors[0], io->left_motors[0], io->right_motors[0]);
    belev = new BelevatorControl();
    winch = new WinchControl();

    auto_ = new AutoControl(drive);
  }

  void AutonomousInit() {
    cout << "Auto Init" << endl;
    auto io = IO::get_instance();
    io->navx->ZeroYaw();

    auto_->init();
  }
  void AutonomousPeriodic() {
    auto_->tick();
    drive->strategy_controller().periodic();
    drive->log_write(); // Make this bit call only on mutates later *
    // belev->log_write();
    // winch->log_write();
  }

  void TeleopInit() {
    cout << "Teleop Init" << endl;
    ControlMap::init();

    auto strat = make_shared<DriveStarategy>(drive);
    drive->strategy_controller().set_active(strat);
  }
  void TeleopPeriodic() {
    drive->strategy_controller().periodic();

    belev->lift_speed(ControlMap::belevator_motor_power());
    belev->claw(ControlMap::intake_claw_state());
    belev->intake(ControlMap::intake_motor_power());

    winch->send_to_robot(ControlMap::winch_power());
  }

  void TestInit() {
    auto io = IO::get_instance();
    auto strat = std::make_shared<curtinfrc::MotionProfileTunerStrategy>(
      io->left_motors[0], io->right_motors[0],
      io->navx, 1440, 6
    );
    drive->strategy_controller().set_active(strat);
  }

  void TestPeriodic() {
    drive->strategy_controller().periodic();
  }
};

START_ROBOT_CLASS(Robot)
