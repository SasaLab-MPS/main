/*=====================================================================
  setMinimumPressure.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void setMinimumPressure(void)
{
    double xij, yij, zij, distance2;
    int i, j;

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == GHOST || ParticleType[i] == DUMMY_WALL)
            continue;
        MinimumPressure[i] = Pressure[i];
        for (j = 0; j < NumberOfParticles; j++)
        {
            if ((j == i) || (ParticleType[j] == GHOST))
                continue;
            if (ParticleType[j] == DUMMY_WALL)
                continue;
            xij = Position[j * 3] - Position[i * 3];
            yij = Position[j * 3 + 1] - Position[i * 3 + 1];
            zij = Position[j * 3 + 2] - Position[i * 3 + 2];
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            if (distance2 >= Re2_forGradient)
                continue;
            if (MinimumPressure[i] > Pressure[j])
            {
                MinimumPressure[i] = Pressure[j];
            }
        }
    }
}
