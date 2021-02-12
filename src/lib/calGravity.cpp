/*=====================================================================
  calGravity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  NS方程式右辺第三項を計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void calGravity( void ){
  int i;    //  粒子番号

  for(i=0; i < NumberOfParticles; i++) {    // NumberOfParticles:粒子の総数
      if (ParticleType[i] == FLUID)
      {
          // 流体粒子⇒重力加速度を設定
          Acceleration[i * 3] = G_X;
          Acceleration[i * 3 + 1] = G_Y;
          Acceleration[i * 3 + 2] = G_Z;
      }
      else
      {
          Acceleration[i * 3] = 0.0;
          Acceleration[i * 3 + 1] = 0.0;
          Acceleration[i * 3 + 2] = 0.0;
      }
  }
}