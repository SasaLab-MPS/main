/*=====================================================================
  calViscosity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  NS方程式右辺第二項を計算
  Last update: Feb 21, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calViscosity(void)
{
    double viscosityTerm_x, viscosityTerm_y, viscosityTerm_z; //  粘性による粒子の各方向への加速
    double distance, distance2;
    double w;
    double xij, yij, zij;
    double a;

    a = (KINEMATIC_VISCOSITY) * (2.0 * DIM) / (N0_forLaplacian * Lambda); // 係数
    calBkt();   // 粒子が所属するバケットを計算
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType != FLUID)
            continue;
        // 粘性力による加速度の初期化
        viscosityTerm_x = 0.0;
        viscosityTerm_y = 0.0;
        viscosityTerm_z = 0.0;

        searchBkt(i);
        int j;
        for(int k = 0; k < (int)neghPar.size(); k++) {
            j = neghPar[k];     // particle jの番号
            if ((j == i) || (position[j].particleType == GHOST))
                continue; // その粒子自身とゴースト粒子は計算に含めない
            // 粒子間距離の計算
            xij = position[j].x - position[i].x;
            yij = position[j].y - position[i].y;
            zij = position[j].z - position[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 影響範囲か？
            if (distance < Re_forLaplacian)
            {
                w = weight(distance, Re_forLaplacian); // 重み関数
                viscosityTerm_x += (velocity[j].x - velocity[i].x) * w;
                viscosityTerm_y += (velocity[j].y - velocity[i].y) * w;
                viscosityTerm_z += (velocity[j].z - velocity[i].z) * w;
            }
        }

        // 粘性による粒子の加速を計算
        viscosityTerm_x = viscosityTerm_x * a;
        viscosityTerm_y = viscosityTerm_y * a;
        viscosityTerm_z = viscosityTerm_z * a;
        acceleration[i].x += viscosityTerm_x;
        acceleration[i].y += viscosityTerm_y;
        acceleration[i].z += viscosityTerm_z;
    }
}