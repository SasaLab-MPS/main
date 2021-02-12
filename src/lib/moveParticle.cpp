/*=====================================================================
  mpveParticle.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の移動を計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void moveParticle(void)
{
    int i;  // 粒子番号

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == FLUID)
        {
            // 速度の更新
            Velocity[i * 3] += Acceleration[i * 3] * DT;
            Velocity[i * 3 + 1] += Acceleration[i * 3 + 1] * DT;
            Velocity[i * 3 + 2] += Acceleration[i * 3 + 2] * DT;

            // 位置の更新
            Position[i * 3] += Velocity[i * 3] * DT;
            Position[i * 3 + 1] += Velocity[i * 3 + 1] * DT;
            Position[i * 3 + 2] += Velocity[i * 3 + 2] * DT;
        }

        // 加速度の初期化
        Acceleration[i * 3] = 0.0;
        Acceleration[i * 3 + 1] = 0.0;
        Acceleration[i * 3 + 2] = 0.0;
    }
}