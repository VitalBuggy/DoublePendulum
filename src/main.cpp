#include "./core/DoublePendulum.hpp"

int main(int argc, char* argv[])
{
  // TODO: Add a gui feature for the user to set these conditions during runtime
  DPMath::DPendulumInitConditions conditions;
  conditions.angle1 = PI/4;
  conditions.angle2 = PI/2;
  conditions.angle1_dp = 0;
  conditions.angle2_dp = 0;
  conditions.g = 1;
  conditions.length1 = 200;
  conditions.length2 = 200;
  conditions.mass1 = 20;
  conditions.mass2 = 20;
  DoublePendulum dp(800, 1000, conditions);
  dp.run(60);
}
