/*=====================================================================
  calTemperatureLaplacian.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱分布を計算
  Last update: Mar 15, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calTemperatureLaplacian(void){
    double distance, distance2;
    double w;
    double xij, yij, zij;
    double rho, c, lmb;
    double a, b;           // 係数
    double alpha, beta;    // α：温度伝導率，β：係数
    double aij, aii;       //係数行列の係数

    // 計算用の配列
    //vector<double> dH;
    //dH.resize(NumberOfParticles, 0.0);
     
    rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
    c = SPECIFIC_HEAT_CAPACITY; // 比熱容量
    lmb = HEAT_CONDUCTIVITY;    // 熱伝導率

    a = (2.0 * DIM) / (N0_forLaplacian * Lambda);
    b = 1 / (rho * c);

    alpha = lmb / (rho * c);    // 温度伝導率
    beta = a * alpha;

    calBucket(); // 粒子が所属するバケットを計算

    for (int i = 0; i < NumberOfParticles; i++)
    {
        // 要検討
        /*
        if (position[i].particleType == WALL || position[i].particleType == DUMMY_WALL || position[i].particleType == GHOST)
            continue;
        */
        aij = 0.0;
        aii = 0.0;
        searchBucket(i);
        int j;
        for (int k = 0; k < (int)neghPar.size(); k++)
        {
            j = neghPar[k]; // particle jの番号
            if (j == i)
                continue;   // その粒子自身は計算に含めない

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
                aij = - beta * (temperature[j] - temperature[i]) * w * DT;
                aii += aij;
                Aij.push_back( Tri(i, j, aij) );
            }
            aii += 1;
            Aij.push_back( Tri(i, i, aii) );
        }
        //dH[i] = a * Aij;
    }
}