/*=====================================================================
  moveParticle.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の移動を計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void moveParticle(void)
{
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (particle[i].particleType == FLUID)
        {
            // 速度の更新:v=at
            velocity[i].x += acceleration[i].x * DT;
            velocity[i].y += acceleration[i].y * DT;
            velocity[i].z += acceleration[i].z * DT;

            // 位置の更新:x=vt
            particle[i].x += velocity[i].x * DT;
            particle[i].y += velocity[i].y * DT;
            particle[i].z += velocity[i].z * DT;
        }

        // 加速度の初期化
        acceleration[i].x = 0.0;
        acceleration[i].y = 0.0;
        acceleration[i].z = 0.0;
    }
    // 計算範囲外に出た粒子を処理
    checkParticle();
    // 粒子が所属するバケットを計算
    calBucket();
}