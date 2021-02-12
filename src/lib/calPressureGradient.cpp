/*=====================================================================
  calPressureGradient.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力勾配による加速度ベクトル(右辺第二項)の計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

// グラディエントモデル
void calPressureGradient(void)
{
    int i, j;
    double gradient_x, gradient_y, gradient_z;
    double xij, yij, zij;
    double distance, distance2;
    double w, pij;
    double a;

    a = DIM / N0_forGradient;
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] != FLUID)
            continue;
        gradient_x = 0.0;
        gradient_y = 0.0;
        gradient_z = 0.0;
        for (j = 0; j < NumberOfParticles; j++)
        {
            if (j == i)
                continue;
            if (ParticleType[j] == GHOST)
                continue;
            if (ParticleType[j] == DUMMY_WALL)
                continue;
            xij = Position[j * 3] - Position[i * 3];
            yij = Position[j * 3 + 1] - Position[i * 3 + 1];
            zij = Position[j * 3 + 2] - Position[i * 3 + 2];
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            if (distance < Re_forGradient)
            {
                w = weight(distance, Re_forGradient);
                pij = (Pressure[j] - MinimumPressure[i]) / distance2;   // グラディエントモデル(最小圧力を用いることで値を正に保つ)
                // 総和計算
                gradient_x += xij * pij * w;
                gradient_y += yij * pij * w;
                gradient_z += zij * pij * w;
            }
        }
        gradient_x *= a;
        gradient_y *= a;
        gradient_z *= a;
        Acceleration[i * 3] = (-1.0) * gradient_x / FluidDensity;
        Acceleration[i * 3 + 1] = (-1.0) * gradient_y / FluidDensity;
        Acceleration[i * 3 + 2] = (-1.0) * gradient_z / FluidDensity;
    }
}
