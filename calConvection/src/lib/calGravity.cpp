/*=====================================================================
  calGravity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  NS方程式右辺第三項を計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calGravity(void)
{
    double beta = 3 * LINEAR_EXPANSION_COEFFICIENT; // 体積膨張率
    double T0 = INITIAL_TEMPERATURE;
    double boussinesq;      // ブシネスク近似

    for (int i = 0; i < NumberOfParticles; i++)
    { // NumberOfParticles:粒子の総数
        if (position[i].particleType == FLUID)
        {
            boussinesq = (-1) * beta * (temperature[i] - T0);  // -β(T - T0)
            // 流体粒子の重力加速度を設定・ブシネスク近似を導入
            acceleration[i].x = boussinesq * G_X;
            acceleration[i].y = boussinesq * G_Y;
            acceleration[i].z = boussinesq * G_Z;
        }
        else
        {
            // 流体粒子でなければ加速度なし
            acceleration[i].x = 0.0;
            acceleration[i].y = 0.0;
            acceleration[i].z = 0.0;
        }
    }
}