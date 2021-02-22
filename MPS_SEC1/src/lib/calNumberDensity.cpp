/*=====================================================================
  calNumberDensity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子数密度を計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calNumberDensity(void)
{
    double xij, yij, zij;
    double distance, distance2;
    double w;
    numberDensity.resize(NumberOfParticles);

    calBkt(); // 粒子が所属するバケットを計算
    for (int i = 0; i < NumberOfParticles; i++)
    {
        numberDensity[i] = 0.0;
        if (position[i].particleType == GHOST)
            continue;

        /* バケット法による粒子の探索効率向上 */
        searchBkt(i); // 粒子i近傍の粒子をneghParにリスト化
        int j;        // particle j
        for(int k = 0; k < neghPar.size(); k++) {
            j = neghPar[k];
            if ((j == i) || (position[j].particleType == GHOST))
                continue; // その粒子自身とゴースト粒子は計算に含めない
            // 粒子間距離の計算
            xij = position[j].x - position[i].x;
            yij = position[j].y - position[i].y;
            zij = position[j].z - position[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 重み関数の計算
            w = weight(distance, Re_forNumberDensity);
            numberDensity[i] += w;
        }
    }
}