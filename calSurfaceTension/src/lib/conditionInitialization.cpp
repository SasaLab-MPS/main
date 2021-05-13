/*=====================================================================
  conditionInitialization.cpp   
  Yota INOUE (2021) 
  変数定義ファイル
  Last update: Mar 30, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void conditionInitialization(void) {
    if (DIM == 2) {
        initializeParticlePositionAndVelocity_for2dim();
    } else {
        initializeParticlePositionAndVelocity_for3dim();
    }

    /* ---バケット法探索の下準備--- */
    structBucket();  // バケットの構築
    calBucket();     // バケットに粒子を入れる
    checkParticle(); // 計算範囲外に出た粒子を処理

    // 計算に使用する行列，ベクトルの設定, 初期化
    int NP = NumberOfParticles;
    /* ---圧力計算用--- */
    coefficientMatrix.resize(NP, NP);
    sourceTerm.setZero(NP);
    pressure.setZero(NP);
    numberDensity.resize(NP, 0);

    /* ---温度計算用--- */
    temperature.setZero(NP);                // 全粒子に初期温度を与える
    //enthalpy.resize(NP, 0);
    initializeTemperatureDistribution();    // 温度分布の初期化
}