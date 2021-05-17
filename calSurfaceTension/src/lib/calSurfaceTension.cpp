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
    double beta = THRESHOLD_RATIO_OF_NUMBER_DENSITY;

    calNumberDensity();   // 密度計算

    // 表面張力計算本体
    for(int i = 0; i < NumberOfParticles; i++) 
    {
      // 表面張力の初期化
      surfaceTension[i].x = 0.0;
      surfaceTension[i].y = 0.0;
      surfaceTension[i].z = 0.0;

      calNormalVector(i);         // 法線ベクトル計算

      // 自由表面ならば表面張力を計算
      if (numberDensity[i] < beta * N0_forNumberDensity)
      {
        kappa = calCurvature(i);  // 曲率
        //cout << "kappa:" << kappa << endl;
        a = SIGMA * kappa;
        // 表面張力計算
        surfaceTension[i].x = a * normalVector[i].x;
        surfaceTension[i].y = a * normalVector[i].y;
        surfaceTension[i].z = a * normalVector[i].z;
      }
 
      // 表面張力による粒子の加速を計算
      acceleration[i].x += surfaceTension[i].x / FLUID_DENSITY;
      acceleration[i].y += surfaceTension[i].y / FLUID_DENSITY;
      acceleration[i].z += surfaceTension[i].z / FLUID_DENSITY;
    }

}