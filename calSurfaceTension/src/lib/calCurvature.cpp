/*=====================================================================
  calCurvature.cpp   
  Yota INOUE (2021) 
  表面張力の曲率
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double calCurvature(int particleNumber) {
  double theta;
  double kappa;

  theta = 0.5 * M_PI * numberDensity[particleNumber] / N0_forNumberDensity;
  kappa = 2 * cos(theta) / RADIUS_FOR_LAPLACIAN;

  return kappa;
}