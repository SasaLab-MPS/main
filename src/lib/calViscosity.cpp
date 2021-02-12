/*=====================================================================
  calViscosity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  NS方程式右辺第二項を計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void calViscosity(void)
{
    int i, j;
    double viscosityTerm_x, viscosityTerm_y, viscosityTerm_z;   //  粘性による粒子の各方向への加速
    double distance, distance2;
    double w;
    double xij, yij, zij;
    double a;

    a = (KINEMATIC_VISCOSITY) * (2.0 * DIM) / (N0_forLaplacian * Lambda);   // 係数
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] != FLUID)
            continue;
        // 粘性力による加速度の初期化
        viscosityTerm_x = 0.0;
        viscosityTerm_y = 0.0;
        viscosityTerm_z = 0.0;

        for (j = 0; j < NumberOfParticles; j++)
        {
            if ((j == i) || (ParticleType[j] == GHOST)) // その粒子自身とゴースト粒子は計算に含めない
                continue;
            // 粒子間距離の計算
            xij = Position[j * 3] - Position[i * 3];
            yij = Position[j * 3 + 1] - Position[i * 3 + 1];
            zij = Position[j * 3 + 2] - Position[i * 3 + 2];
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 影響範囲か？
            if (distance < Re_forLaplacian)
            {
                w = weight(distance, Re_forLaplacian);  // 重み関数
                viscosityTerm_x += (Velocity[j * 3] - Velocity[i * 3]) * w;
                viscosityTerm_y += (Velocity[j * 3 + 1] - Velocity[i * 3 + 1]) * w;
                viscosityTerm_z += (Velocity[j * 3 + 2] - Velocity[i * 3 + 2]) * w;
            }
        }

        // 粘性による粒子の加速を計算
        viscosityTerm_x = viscosityTerm_x * a;
        viscosityTerm_y = viscosityTerm_y * a;
        viscosityTerm_z = viscosityTerm_z * a;
        Acceleration[i * 3] += viscosityTerm_x;
        Acceleration[i * 3 + 1] += viscosityTerm_y;
        Acceleration[i * 3 + 2] += viscosityTerm_z;
    }
}
