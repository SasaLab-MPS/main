/*=====================================================================
  calPressureGradient.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力勾配による加速度ベクトル(右辺第二項)の計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

// グラディエントモデル
void calPressureGradient(void)
{
    double gradient_x, gradient_y, gradient_z;
    double xij, yij, zij;
    double distance, distance2;
    double w, pij;
    double a;

    a = DIM / N0_forGradient;
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (particle[i].particleType != FLUID) { continue; }
        gradient_x = 0.0;
        gradient_y = 0.0;
        gradient_z = 0.0;

        searchBucket(i);
        int j;
        for(int k = 0; k < (int)neghPar.size(); k++) {
            j = neghPar[k];
            if (j == i) { continue; }
            if (particle[j].particleType == GHOST) { continue; }
            if (particle[j].particleType == DUMMY_WALL) { continue; }
            xij = particle[j].x - particle[i].x;
            yij = particle[j].y - particle[i].y;
            zij = particle[j].z - particle[i].z;
            
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            if (distance < Re_forGradient)
            {
                w = weight(distance, Re_forGradient);
                pij = (pressure(j) - minimumPressure[i]) / distance2; // グラディエントモデル(最小圧力を用いることで値を正に保つ)
                // 総和計算
                gradient_x += xij * pij * w;
                gradient_y += yij * pij * w;
                gradient_z += zij * pij * w;
            }
        }
        
        gradient_x *= a;
        gradient_y *= a;
        gradient_z *= a;
        acceleration[i].x = (-1.0) * gradient_x / FluidDensity;
        acceleration[i].y = (-1.0) * gradient_y / FluidDensity;
        acceleration[i].z = (-1.0) * gradient_z / FluidDensity;
    }
}