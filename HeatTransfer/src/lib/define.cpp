/*=====================================================================
  define.cpp   
  Yota INOUE (2021) 
  変数定義ファイル
  Last update: Mar 30, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

/* 動的配列 */
vector<Position> position;         // 位置
vector<Velocity> velocity;         // 速度
vector<Acceleration> acceleration; // 加速度
// constantParameterで定義
MatrixXd coefficientMatrix;         // A:係数行列 = CoefficientMatrix
VectorXd sourceTerm, pressure;      // b:右辺係数，x:圧力の列ベクトル
vector<double> numberDensity;       // 粒子密度
vector<double> temperature;         // 温度
vector<double> enthalpy;            // エンタルピー
//vector<double> minimumTemperature;  // 周辺の最低温度
//vector<double> heatFlux;                   // 熱流束
vector<double> minimumPressure;     // ある粒子近傍での最低圧力
// 境界条件に関わる変数
vector<int> boundaryCondition;                  // ディリクレ境界条件を付加するかどうかのフラグ
vector<int> flagForCheckingBoundaryCondition;   // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ

/* グローバル変数定義 */
int FileNumber;
double Time = 0.0;
int NumberOfParticles;                          // 全粒子数
double Re_forNumberDensity, Re2_forNumberDensity;
double Re_forGradient, Re2_forGradient;
double Re_forLaplacian, Re2_forLaplacian;       // Re:ラプラシアンモデルの影響範囲, calConstantParameterで設定
double N0_forNumberDensity;                     // 粒子数密度
double N0_forGradient;
double N0_forLaplacian;
double Lambda;
double collisionDistance, collisionDistance2;
double FluidDensity;
double x_MAX = 0.5, y_MAX = 0.5, z_MAX = 0.1;       // 計算領域の最大値
double Pos_MIN[3] = {0.0, 0.0, 0.0};                // 計算領域の最小値:struktBktで使用

// バケット探索法に関わる変数・配列
vector<vector<int>> bucket;                     // バケットid，structBktで定義
vector<int> neghPar;                            // 対象の粒子近傍の粒子リスト
double DB, DB2, DBinv;                          // バケット一辺の長さ，その二乗，逆数
int buckets;                                    // バケットの総数
int nBx, nBy, nBz, nBxy, nBxyz;                 // x, y, z方向のバケット数とその積
