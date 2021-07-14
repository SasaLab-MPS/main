/*=====================================================================
  setMinimumPressure.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 28, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setMinimumPressure(void)
{
    double xij, yij, zij, distance2;
    minimumPressure.resize(NumberOfParticles);

    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (particle[i].particleType == GHOST || particle[i].particleType == DUMMY_WALL)
            continue;
        minimumPressure[i] = pressure(i);

        searchBucket(i);
        int j;
        for(int k = 0; k < (int)neghPar.size(); k++) {
            j = neghPar[k];
            if ((j == i) || (particle[j].particleType == GHOST))
                continue;
            if (particle[j].particleType == DUMMY_WALL)
                continue;
            xij = particle[j].x - particle[i].x;
            yij = particle[j].y - particle[i].y;
            zij = particle[j].z - particle[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            if (distance2 >= Re2_forGradient)
                continue;
            if (minimumPressure[i] > pressure(j))
            {
                minimumPressure[i] = pressure(j);
            }
        }
    }
}