/*=====================================================================
  functions.hpp   
  Yota INOUE (2021) 
  粒子法プログラムの関数定義ファイル
  Last update: Feb 20, 2021
=======================================================================*/
//#include "functions.hpp"
#ifndef FUNCTIONS_HPP_20210220_222753_
#define FUNCTIONS_HPP_20210220_222753_

#include "constants.hpp"

void conditionInitialization(void);                            // 計算領域の初期化 
void initializeParticlePositionAndVelocity_for2dim(void);      // t = 0sでの粒子の速度と位置を決定 (2次元)
void initializeParticlePositionAndVelocity_for3dim(void);      // t = 0sでの粒子の速度と位置を決定 (3次元)
void initializeTemperatureDistribution(void);                  // 温度分布の初期化 
void calConstantParameter(void);                               // 影響半径などの定数計算
void calNZeroAndLambda(void);                                  // 初期粒子密度 n0および lambdaの計算
double weight(double distance, double re);                     // 重み関数の計算
void structBucket(void);                                       // 解析領域にバケット領域を生成する関数
void calBucket(void);                                          // 粒子の所属するバケットを計算する関数，calViscosityで使用
void mainLoopOfSimulation(void);                               // メインループ
void writeData_inProfFormat(void);                             // 計算結果の出力(独自ファイル形式)
void writeData_inVtuFormat(void);                              // 計算結果をファイル出力(ParaViewのvtuファイル形式)
void writeData_inTemperatureFormat(void);                      // 計算結果をファイル出力(csvファイル形式)
void calGravity(void);                                         // NS方程式右辺第三項を計算，重力による粒子の加速を計算
void calViscosity(void);                                       // NS方程式右辺第二項を計算，粘性による粒子の加速を計算
void moveParticle(void);                                       // 粒子の移動を計算
void collision(void);                                          // 剛体衝突関数(粒子同士が異常接近した場合に粒子間の距離を広げる)
void calPressure(void);                                        // 圧力を計算(陰解法)
void calNumberDensity(void);                                   // 粒子数密度の計算
void setBoundaryCondition(void);                               // 圧力のポアソン方程式にディリクレ境界条件を付与
void setSourceTerm(void);                                      // 圧力のポアソン方程式のソース項の計算
void setMatrix(void);                                          // 連立一次方程式の係数行列を設定
void exceptionalProcessingForBoundaryCondition(void);          // 自由表面が無い粒子集合に対する例外処理
void searchBucket(int i);                                      // 粒子i近傍の粒子を探索する関数
void checkBoundaryCondition(void);                             // ポアソン方程式のディリクレ境界条件のチェック
void increaseDiagonalTerm(void);                               // 連立一次方程式の係数行列の対角項を大きくする例外処理
void solvePressureByCGmethod(void);                            // CG法による高速解法，calPressureで使用
void removeNegativePressure(void);                             // 負圧が生じた場合，0 Paに修正
void setMinimumPressure(void);                                 // ある粒子近傍で最低圧力を記録
void calPressureGradient(void);                                // 圧力勾配による加速度ベクトルの計算
void moveParticleUsingPressureGradient(void);                  // 圧力勾配による加速度ベクトルの計算を元に粒子を移動
void checkParticle(void);                                      // 計算領域外に出た粒子を処理
/* --- 熱伝導計算 --- */
void calTemperature(void);                                     // 温度分布を計算
void setTemperatureDistribution(void);                         // 初期温度分布を与える
void calTemperatureLaplacian(void);                            // 温度のラプラシアンを計算
void solveTemperatureByCGmethod(void);                         // 温度をCG法により高速解放
void removeNegativeTemperature(void);                          // 温度が最低温度未満になった場合を0処理
void setTemperatureBoundaryCondition(void);                    // 温度のチェック
void checkNeumannBoundaryCondition(void);                      // 境界条件の設定(ノイマン境界条件)
/* ---表面張力計算--- */
void calSurfaceTension(void);                                  // 表面張力計算本体
void calNormalVector(void);                                    // 表面の法線ベクトル
double calCurvature(int particleNumber);                       // 表面粒子の曲率, kappa

/* ---レーザ照射中の各値を計算--- */
void calScanPath(int strategy);                                // 走査経路を計算
void islandPattern(void);                                      // アイランドスキャン
void stripePattern(void);                                      // ストライプスキャン
double calLaserIntensity(Particle point);                      // レーザの強度分布を計算

/* ---粉末の熱伝導率を計算--- */
double calPowderHeatTransfer(double tmp);                      // 粉末の熱伝導率を計算

#endif // FUNCTIONS_HPP_20210220_222753_