/*=====================================================================
  calTemperature.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱分布を計算
  Last update: Mar 15, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calTemperature(void) {
    double distance, distance2;
    double w;
    double xij, yij, zij;
    double a, rho, c, lmb;
    double Ti;
    a = (2.0 * DIM) / (N0_forLaplacian * Lambda); // 係数
    rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
    c = SPECIFIC_HEAT;          // 比熱容量
    lmb = HEAT_CONDUCTIVITY;    // 熱伝導率
    calBucket();                // 粒子が所属するバケットを計算

    for (int i = 0; i < NumberOfParticles; i++)
    {
        // 要検討
        if (position[i].particleType != SOLID || position[i].particleType != FLUID || position[i].particleType != GAS)
            continue;

        Ti = 0.0;
        searchBucket(i);
        int j;
        for (int k = 0; k < (int)neghPar.size(); k++)
        {
            j = neghPar[k]; // particle jの番号
            if ((j == i) || (position[j].particleType == GHOST))
                continue;   // その粒子自身とゴースト粒子は計算に含めない
            // 粒子間距離の計算
            xij = position[j].x - position[i].x;
            yij = position[j].y - position[i].y;
            zij = position[j].z - position[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 影響範囲か？
            if (distance < Re_forLaplacian)
            {
                cout << "cal Temperature" << endl;
                w = weight(distance, Re_forLaplacian); // 重み関数
                temperature[j] += (1/(rho*c))*(lmb*a*temperature[j] + heatFlux[i])*w;
                Ti += temperature[j];
            }
            temperature[i] = Ti;
        }
    }
}