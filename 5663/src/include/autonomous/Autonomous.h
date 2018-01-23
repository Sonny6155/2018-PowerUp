#pragma once

#include "WPILib.h"
#include "components/Drive.h"
#include "components/Lift.h"
#include "components/Manipulator.h"
#include "components/Ramp.h"
#include <string>

using namespace components;

namespace autonomous {
  class Autonomous {
    Lift *autoLift;
    Drive *autoDrive;
    Manipulator *autoMan;
    public:
      Autonomous(Drive drive, Lift lift, Manipulator man, Ramp ramp);
      void ChooseRoutine(int autoMode, int startingPosition);
      void RunPeriodic();
    private:
      void Baseline();
      void S1L();
      void S2L();
      void S3L();
      void S1R();
      void S2R();
      void S3R();

      std::string gameData;
      std::function<void()> autoFunction;
      int AutoStage = 0;
  };
}
