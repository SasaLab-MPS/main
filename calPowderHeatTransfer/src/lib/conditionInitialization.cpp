/*=====================================================================
  conditionInitialization.cpp   
  Yota INOUE (2021) 
  変数定義ファイル
  Last update: Mar 30, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

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

    /* 計算に使用する行列，ベクトルの設定, 初期化 */
    int NP = NumberOfParticles;
    // 圧力計算用
    coefficientMatrix.resize(NP, NP);
    sourceTerm.setZero(NP);
    pressure.setZero(NP);
    numberDensity.resize(NP, 0);
    // 温度計算用
    Tmp.resize(NP, NP);
    temperature.setZero(NP);                // 全粒子に初期温度を与える
    initializeTemperatureDistribution();    // 温度分布の初期化
    ThermalConductivity.resize(NP);         // 熱伝導率の設定
    initializeThermalConductivity();        // 熱伝導率の初期化

    /* ---走査パターン計算用---*/
    // 初期設定，レーザの中心は左下
    if (DIM == 2) {
        centerOfLaser = {0.0, 0.0, 0.0};
    } else {
        centerOfLaser = {0.0, 0.0, z_MAX};
    }  
    referencePoint = centerOfLaser;
    NumOfStrategy = 0;
    ScanDirection = Y_FORWARD;
}