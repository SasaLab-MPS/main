/*=====================================================================
  moveParticleUsingPressureGradient.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void moveParticleUsingPressureGradient(void)
{
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == FLUID)
        {
            Velocity[i * 3] += Acceleration[i * 3] * DT;
            Velocity[i * 3 + 1] += Acceleration[i * 3 + 1] * DT;
            Velocity[i * 3 + 2] += Acceleration[i * 3 + 2] * DT;

            Position[i * 3] += Acceleration[i * 3] * DT * DT;
            Position[i * 3 + 1] += Acceleration[i * 3 + 1] * DT * DT;
            Position[i * 3 + 2] += Acceleration[i * 3 + 2] * DT * DT;
        }
        Acceleration[i * 3] = 0.0;
        Acceleration[i * 3 + 1] = 0.0;
        Acceleration[i * 3 + 2] = 0.0;
    }
}
