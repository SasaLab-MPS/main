/*=====================================================================
  moveParticleUsingPressureGradient.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void moveParticleUsingPressureGradient(void)
{
    int i;

    for (i = 0; i < NumberOfParticles; i++)
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
