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
    double a;              // ラプラシアンモデルの係数
    double alpha, beta;    // α：温度伝導率，β：係数
    double aij, aii;       //係数行列の各値

    rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
    c = SPECIFIC_HEAT_CAPACITY; // 比熱容量
    lmb = HEAT_CONDUCTIVITY;    // 熱伝導率

    a = (2.0 * DIM) / (N0_forLaplacian * Lambda);

    alpha = lmb / (rho * c);    // 温度伝導率
    beta = a * alpha;

    calBucket();    // 粒子が所属するバケットを計算
    T_aij.clear();  // 係数行列の初期化

    for (int i = 0; i < NumberOfParticles; i++)
    {
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
            xij = particle[j].x - particle[i].x;
            yij = particle[j].y - particle[i].y;
            zij = particle[j].z - particle[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 影響範囲内か
            if (distance < Re_forLaplacian) {
                w = weight(distance, Re_forLaplacian); // 重み関数
                aij = beta * w * DT;
                aii += aij;
                T_aij.push_back(Tri(i, j, (-1) * aij));
            }
        }
        aii += 1;
        T_aij.push_back(Tri(i, i, aii));
    }
}