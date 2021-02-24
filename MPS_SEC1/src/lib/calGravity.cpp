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
    int i; //  粒子番号
    for (i = 0; i < NumberOfParticles; i++)
    { // NumberOfParticles:粒子の総数
        if (position[i].particleType == FLUID)
        {
            // 流体粒子の重力加速度を設定
            acceleration[i].x = G_X;
            acceleration[i].y = G_Y;
            acceleration[i].z = G_Z;
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