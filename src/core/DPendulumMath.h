#ifndef _DPMATH
#define _DPMATH

#include <bits/stdc++.h>
namespace DPMath {

struct DPendulumInitConditions {
  double g;
  double length1, mass1, angle1, angle1_dp;
  double length2, mass2, angle2, angle2_dp;
};

inline std::pair<double, double> calculate_dv(DPendulumInitConditions *conditions) {
  double num1 = -(conditions->g) * (2 * (conditions->mass1) + (conditions->mass2)) * sin((conditions->angle1));
  double num2 = -(conditions->mass2) * (conditions->g) * sin((conditions->angle1) - 2 * (conditions->angle2));
  double num3 = -2 * sin((conditions->angle1) - (conditions->angle2)) * (conditions->mass2);
  double num4 = (conditions->angle2_dp) * (conditions->angle2_dp) * (conditions->length2) + (conditions->angle1_dp) * (conditions->angle1_dp) * (conditions->length1) * cos((conditions->angle1) - (conditions->angle2));
  double den = (conditions->length1) * (2 * (conditions->mass1) + (conditions->mass2) - (conditions->mass2) * cos(2 * (conditions->angle1) - 2 * (conditions->angle2)));
  double a1_dv = (num1 + num2 + num3 * num4) / den;

  num1 = 2 * sin((conditions->angle1) - (conditions->angle2));
  num2 = ((conditions->angle1_dp) * (conditions->angle1_dp) * (conditions->length1) * ((conditions->mass1) + (conditions->mass2)));
  num3 = (conditions->g) * ((conditions->mass1) + (conditions->mass2)) * cos((conditions->angle1));
  num4 = (conditions->angle2_dp) * (conditions->angle2_dp) * (conditions->length2) * (conditions->mass2) * cos((conditions->angle1) - (conditions->angle2));
  den = (conditions->length2) * (2 * (conditions->mass1) + (conditions->mass2) - (conditions->mass2) * cos(2 * (conditions->angle1) - 2 * (conditions->angle2)));
  double a2_dv = (num1 * (num2 + num3 + num4)) / den;

  return {a1_dv, a2_dv};
}

}; // namespace DPMath

#endif