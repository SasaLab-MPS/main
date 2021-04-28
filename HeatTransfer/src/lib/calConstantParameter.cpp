/*=====================================================================
  calConstantParameter.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 20, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

// 影響半径などの定数計算
void calConstantParameter(void) {
  Re_forNumberDensity = RADIUS_FOR_NUMBER_DENSITY;
  Re_forGradient = RADIUS_FOR_GRADIENT;
  Re_forLaplacian = RADIUS_FOR_LAPLACIAN;

  Re2_forNumberDensity = Re_forNumberDensity * Re_forNumberDensity;
  Re2_forGradient = Re_forGradient * Re_forGradient;
  Re2_forLaplacian = Re_forLaplacian * Re_forLaplacian;
    
  calNZeroAndLambda();
    
  FluidDensity = FLUID_DENSITY;
  collisionDistance = COLLISION_DISTANCE;
  collisionDistance2 = collisionDistance * collisionDistance;
  FileNumber = 0;
  Time = 0.0;

  structBucket();  // バケットの構築
  calBucket();     // バケットに粒子を入れる
  checkParticle(); // 計算範囲外に出た粒子を処理

  // 行列，ベクトルの設定, 初期化
  int NP = NumberOfParticles;
  coefficientMatrix.setZero(NP, NP);
  sourceTerm.setZero(NP);
  pressure.setZero(NP);
  numberDensity.resize(NP, 0);

  // 熱伝導方程式
  temperature.resize(NP, INITIAL_TEMPERATURE);  // 全粒子に初期温度を与える
  enthalpy.resize(NP, 0);
  heatFlux.resize(NP, 0); // 熱流束

  for (int i = 0; i < NP; i++)
  {
    if (position[i].x < 0.5 * x_MAX)
    {
      temperature[i] = 500;
      enthalpy[i] = 500 * SOLID_DENSITY * SPECIFIC_HEAT_CAPACITY;
    }
    else
    {
      temperature[i] = 300;
      enthalpy[i] = 300 * SOLID_DENSITY * SPECIFIC_HEAT_CAPACITY;
    }
  }
}                               