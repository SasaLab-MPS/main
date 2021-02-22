/*=====================================================================
  functions.hpp   
  Yota INOUE (2021) 
  粒子法プログラムの関数定義ファイル
  Last update: Feb 20, 2021
=======================================================================*/
//#include "functions.hpp"
#ifndef FUNCTIONS_HPP_20210220_222753_
#define FUNCTIONS_HPP_20210220_222753_

// t = 0sでの粒子の速度と位置を決定 (2次元)
void initializeParticlePositionAndVelocity_for2dim(double x_width, double y_height);
// t = 0sでの粒子の速度と位置を決定 (3次元)
void initializeParticlePositionAndVelocity_for3dim(double x_width, double y_height, double z_depth);
void calConstantParameter(void);                               // 影響半径などの定数計算
void calNZeroAndLambda(void);                                  // 初期粒子密度 n0および lambdaの計算
double weight(double distance, double re);                     // 重み関数の計算
void structBkt(void);                                          // 解析領域にバケット領域を生成する関数
void calBkt(void);                                             // 粒子の所属するバケットを計算する関数，calViscosityで使用
void mainLoopOfSimulation(void);                               // メインループ
void writeData_inProfFormat(void);                             // 計算結果の出力(独自ファイル形式)
void writeData_inVtuFormat(void);                              // 計算結果をファイル出力(ParaViewのvtuファイル形式)
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
void searchBkt(int i);                                         // 粒子i近傍の粒子を探索する関数
void checkBoundaryCondition(void);                             // ポアソン方程式のディリクレ境界条件のチェック
void increaseDiagonalTerm(void);                               // 連立一次方程式の係数行列の対角項を大きくする例外処理
void solveByCGmethod(void);                                    // CG法による高速解法，calPressureで使用
void removeNegativePressure(void);                             // 負圧が生じた場合，0 Paに修正
void setMinimumPressure(void);                                 // ある粒子近傍で最低圧力を記録
void calPressureGradient(void);                                // 圧力勾配による加速度ベクトルの計算
void moveParticleUsingPressureGradient(void);                  // 圧力勾配による加速度ベクトルの計算を元に粒子を移動

#endif // FUNCTIONS_HPP_20210220_222753_