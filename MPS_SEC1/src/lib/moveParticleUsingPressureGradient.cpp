/*=====================================================================
  moveParticleUsingPressureGradient.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void moveParticleUsingPressureGradient(void)
{
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType == FLUID)
        {
            velocity[i].x += acceleration[i].x * DT;
            velocity[i].y += acceleration[i].y * DT;
            velocity[i].z += acceleration[i].z * DT;

            position[i].x += acceleration[i].x * DT * DT;
            position[i].y += acceleration[i].y * DT * DT;
            position[i].z += acceleration[i].z * DT * DT;
        }
        acceleration[i].x = 0.0;
        acceleration[i].y = 0.0;
        acceleration[i].z = 0.0;
    }
}