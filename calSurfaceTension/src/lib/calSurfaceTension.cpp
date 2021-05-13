/*=====================================================================
  calSurfaceTension.cpp   
  Yota INOUE (2021) 
  表面張力の計算
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calSurfaceTension(void) {
    double kappa;   // 曲率
    double a;       // 係数
    double phi;
    double beta = THRESHOLD_RATIO_OF_NUMBER_DENSITY;

    calNumberDensity();   // 密度計算
    calNormalVector();    // 法線ベクトル計算

    // 表面張力の計算
    for(int i = 0; i < NumberOfParticles; i++) {

        surfaceTension[i].x = 0.0;
        surfaceTension[i].y = 0.0;
        surfaceTension[i].z = 0.0;

        // 自由表面か ?
        if (numberDensity[i] < beta * N0_forNumberDensity)
        {
          kappa = calCurvature(i);
          a = SIGMA * kappa;

          // 表面張力計算
          surfaceTension[i].x = a * normalVector[i].x;
          surfaceTension[i].y = a * normalVector[i].y;
          surfaceTension[i].z = a * normalVector[i].z;
        }
    }
    
}