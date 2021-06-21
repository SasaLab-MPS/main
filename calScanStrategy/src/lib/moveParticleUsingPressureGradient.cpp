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
        if (particle[i].particleType == FLUID)
        {
            velocity[i].x += acceleration[i].x * DT;
            velocity[i].y += acceleration[i].y * DT;
            velocity[i].z += acceleration[i].z * DT;

            particle[i].x += acceleration[i].x * DT * DT;
            particle[i].y += acceleration[i].y * DT * DT;
            particle[i].z += acceleration[i].z * DT * DT;
        }
        acceleration[i].x = 0.0;
        acceleration[i].y = 0.0;
        acceleration[i].z = 0.0;
    }
    // 計算範囲外に出た粒子を処理
    checkParticle();
}