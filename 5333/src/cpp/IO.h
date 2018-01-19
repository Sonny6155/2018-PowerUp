#pragma once

#include "WPILib.h"
#include "curtinfrc/motors/CurtinTalonSRX.h"
#include "Map.h"

using namespace frc;
using namespace curtinfrc;

class IO {
public:
  int init();

  CurtinTalonSRX *left_motors[2];
  CurtinTalonSRX *right_motors[2];

  CurtinTalonSRX *belev_motors[1];
  CurtinTalonSRX *intake_motors[2][1];

  DoubleSolenoid *intake_solenoids[2];
  DoubleSolenoid *claw_solenoids[1];

  #ifdef XBOX_CONTROL

  XboxController *xbox;

  double get_left_trigger();
  bool get_left_bumper();
  double get_left_X();
  double get_left_Y();
  bool get_left_stick();

  double get_right_trigger();
  bool get_right_bumper();
  double get_right_X();
  double get_right_Y();
  bool get_right_stick();

  bool get_A();
  bool get_B();
  bool get_X();
  bool get_Y();
  bool get_back();
  bool get_start();

  #elif JOY_CONTROL

  Joystick *left_joy, *right_joy;

  double get_left_Y();
  double get_left_X();
  double get_left_twist();

  bool get_left_trigger();


  double get_right_Y();
  double get_right_X();
  double get_right_twist();

  bool get_right_trigger();

  #endif

  static IO *get_instance();
};
