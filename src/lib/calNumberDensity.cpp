/*=====================================================================
  calNumberDensity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子数密度を計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void calNumberDensity(void)
{
    int i, j;
    double xij, yij, zij;
    double distance, distance2;
    double w;

    for (i = 0; i < NumberOfParticles; i++)
    {
        NumberDensity[i] = 0.0;
        if (ParticleType[i] == GHOST)
            continue;
        for (j = 0; j < NumberOfParticles; j++)
        {
            if ((j == i) || (ParticleType[j] == GHOST))
                continue;
            // 粒子間距離の計算
            xij = Position[j * 3] - Position[i * 3];
            yij = Position[j * 3 + 1] - Position[i * 3 + 1];
            zij = Position[j * 3 + 2] - Position[i * 3 + 2];
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 重み関数の計算
            w = weight(distance, Re_forNumberDensity);
            NumberDensity[i] += w;
        }
    }
}
