/*=====================================================================
  setMinimumPressure.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  各粒子近傍で最小の圧力を計算し記録
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setMinimumPressure(void)
{
    double xij, yij, zij, distance2;
    minimumPressure.resize(NumberOfParticles);

    calBkt();
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType == GHOST || position[i].particleType == DUMMY_WALL)
            continue;
        minimumPressure[i] = pressure(i);

        searchBkt(i);
        int j;
        for(int k = 0; k < (int)neghPar.size(); k++) {
            j = neghPar[k];
            if ((j == i) || (position[j].particleType == GHOST))
                continue;
            if (position[j].particleType == DUMMY_WALL)
                continue;
            xij = position[j].x - position[i].x;
            yij = position[j].y - position[i].y;
            zij = position[j].z - position[i].z;
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