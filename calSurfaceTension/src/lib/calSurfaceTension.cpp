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
    double delta;   // デルタ関数の値
    double a;       // 係数
    double phi;

    calNumberDensity();
    calNormalVector();

    // 表面張力の計算
    for(int i = 0; i < NumberOfParticles; i++) {

        kappa = calCurvature(i);
        delta = deltaFunction(phi);

        a = SIGMA * kappa * delta;

        // 表面張力計算
        surfaceTension[i].x = a * normalVector[i].x;
        surfaceTension[i].y = a * normalVector[i].y;
        surfaceTension[i].z = a * normalVector[i].z;
    }
    
}