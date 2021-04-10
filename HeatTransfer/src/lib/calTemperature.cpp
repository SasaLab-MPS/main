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
    double rho, c, lmb;
    double a, b;    // 係数
    double Ti;

    // 計算用の配列
    vector<double> T;
    T.resize(NumberOfParticles);
    for(int i = 0; i < NumberOfParticles; i++) {
        T[i] = temperature[i];
    }
     
    rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
    c = SPECIFIC_HEAT_CAPACITY; // 比熱容量
    lmb = HEAT_CONDUCTIVITY;    // 熱伝導率

    a = lmb * (2.0 * DIM) / (N0_forLaplacian * Lambda);
    b = 1 / (rho * c);

    calBucket(); // 粒子が所属するバケットを計算

    for (int i = 0; i < NumberOfParticles; i++)
    {
        // 要検討
        if (position[i].particleType == WALL || position[i].particleType == DUMMY_WALL || position[i].particleType == GHOST)
            continue;

        Ti = 0.0;   // これで良いのか？
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
            // 影響範囲内か
            if (distance < Re_forLaplacian)
            {
                w = weight(distance, Re_forLaplacian); // 重み関数
                Ti += (temperature[j] - temperature[i]) * w;
            }
        }
        //T[i] = (b * (lmb * a * Ti + heatFlux[i])) * DT;
        T[i] = b * (a*Ti + heatFlux[i]) * DT;
        if (T[i] < INITIAL_TEMPERATURE) {
            T[i] = INITIAL_TEMPERATURE;
        } 
    }

    // 温度の更新
    for (int i = 0; i < NumberOfParticles; i++) {
        temperature[i] += T[i];
        if (temperature[i] > 5000) {
            temperature[i] = 5000;
        }
    }
}