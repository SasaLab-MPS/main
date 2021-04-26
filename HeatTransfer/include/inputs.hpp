/*=====================================================================
  inputs.hpp   
  Yota INOUE (2021) 
  粒子法プログラムの定数定義ファイル
  Last update: Mar 15, 2021
=======================================================================*/
//#include "inputs.hpp"
#ifndef INPUTS_HPP_20210220_220210_
#define INPUTS_HPP_20210220_220210_

#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

/* 定数定義 */
/* for two-dimensional simulation */
constexpr int DIM = 2;                      // 次元
constexpr double PARTICLE_DISTANCE = 0.05;  // 初期粒子間距離 l0 (mm)
constexpr double DT = 0.001;                // 時間刻み幅
constexpr int OUTPUT_INTERVAL = 20;         // 計算結果のファイル出力の間隔

/* for three-dimensional simulation */
/*
constexpr int DIM = 3;
constexpr double PARTICLE_DISTANCE = 0.075;
constexpr double DT = 0.003;
constexpr int OUTPUT_INTERVAL = 20;
*/

constexpr double FINISH_TIME = 0.05;                      // シミュレーションの終了時刻
constexpr double KINEMATIC_VISCOSITY = 1.0e-6;            // 動粘性係数
constexpr double FLUID_DENSITY = 1000.0;                  // 流体の密度
constexpr double G_X = 0.0;
constexpr double G_Y = -9.8;                              // 重力加速度 (m/s^2)
constexpr double G_Z = 0.0;
constexpr double RADIUS_FOR_NUMBER_DENSITY = (2.1 * PARTICLE_DISTANCE);
constexpr double RADIUS_FOR_GRADIENT = (2.1 * PARTICLE_DISTANCE);
constexpr double RADIUS_FOR_LAPLACIAN = (3.1 * PARTICLE_DISTANCE);
constexpr double COLLISION_DISTANCE = (0.5 * PARTICLE_DISTANCE);
constexpr double THRESHOLD_RATIO_OF_NUMBER_DENSITY = 0.97; // 自由表面かを判定する係数β
constexpr double COEFFICIENT_OF_RESTITUTION = 0.2;         // 剛体衝突の反発係数
constexpr double COMPRESSIBILITY = 0.45e-9;                // 流体の圧縮率
constexpr double EPS = (0.01 * PARTICLE_DISTANCE);         // 粒子間隔の100分の1を誤差の判定に利用
constexpr double cgEPS = 1.0e-8;                           // CG法で許容する誤差の上限
constexpr int ON = 1;
constexpr int OFF = 0;
constexpr double RELAXATION_COEFFICIENT_FOR_PRESSURE = 0.2; // 計算を安定させるための緩和係数
constexpr int GHOST = -1;                                   // 計算に関与しない粒子
constexpr int SOLID = 0;                                    // 個体粒子
constexpr int FLUID = 1;                                    // 流体粒子
constexpr int GAS = 2;                                      // 気体粒子
constexpr int POWDER = 3;                                   // 粉末粒子
constexpr int WALL = 12;                                    // (圧力は計算せず，粒子数密度の計算は行う)壁粒子
constexpr int DUMMY_WALL = 13;                              // 仮想的な壁
constexpr int GHOST_OR_DUMMY = -1;                          // ポアソン方程式の計算時に用いる
constexpr int SURFACE_PARTICLE = 1;                         // (圧力を計算する)壁粒子, 最表面の粒子
constexpr int INNER_PARTICLE = 0;                           // 流体内部の粒子
constexpr int DIRICHLET_BOUNDARY_IS_NOT_CONNECTED = 0;      // ディリクレ条件が設定されていない
constexpr int DIRICHLET_BOUNDARY_IS_CONNECTED = 1;          // ディリクレ条件を設定済み
constexpr int DIRICHLET_BOUNDARY_IS_CHECKED = 2;            // ディリクレ条件を満たすことを確認済み
constexpr double CRT_NUM = 0.1;                             // クーラン数

constexpr double INITIAL_TEMPERATURE = 0.0;                 // 初期温度 (℃)
constexpr double SOLID_DENSITY = 2.7e-3;                    // 固体の密度 (g/mm^3)
constexpr double SPECIFIC_HEAT_CAPACITY = 917e-3;           // 比熱容量:c (J/gK)
constexpr double HEAT_CONDUCTIVITY = 238e-3;                // 熱伝導率:λ (J/mmKs)

/* レーザ諸元・造形条件 */
constexpr double LASER_POWER = 300;                         // レーザ出力:P (W, J/s)
constexpr double LASER_DIAMETER = 0.1;                      // レーザ直径:d (mm)
constexpr double SCAN_SPEED = 0.1;                          // レーザ走査速度:v (mm/s)


/* 粒子の座標，速度，速度を表す構造体 */
// 座標:Position
typedef struct
{
  double x;
  double y;
  double z;
  int particleType; // 粒子の状態
} Position;
typedef Position Velocity;                              // 速度:Velocity
typedef Position Acceleration;                          // 加速度:Acceleration

/* 動的配列 */
extern vector<Position> position;                       // 位置
extern vector<Velocity> velocity;                       // 速度
extern vector<Acceleration> acceleration;               // 加速度
extern MatrixXd coefficientMatrix;                      // A:係数行列 = CoefficientMatrix mianLoopで定義
extern VectorXd sourceTerm, pressure;                   // b:右辺係数，x:圧力の列ベクトル
extern vector<double> temperature;                      // 温度
extern vector<double> heatFlux;                         // 熱流束
extern vector<double> numberDensity;                    // 粒子密度
extern vector<int> boundaryCondition;                   // ディリクレ境界条件を付加するかどうかのフラグ
extern vector<int> flagForCheckingBoundaryCondition;    // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ
extern vector<double> minimumPressure;                  // ある粒子近傍での最低圧力
extern vector<vector<int>> bucket;                      // バケットid，structBktで定義
extern vector<int> neghPar;                             // 対象の粒子近傍の粒子, initilizationで定義

/* グローバル変数定義 */
extern int FileNumber;
extern double Time;
extern int NumberOfParticles;                           // 全粒子数
extern double Re_forNumberDensity, Re2_forNumberDensity;
extern double Re_forGradient, Re2_forGradient;
extern double Re_forLaplacian, Re2_forLaplacian;        // Re:ラプラシアンモデルの影響範囲, calConstantParameterで設定
extern double N0_forNumberDensity;                      // 粒子数密度
extern double N0_forGradient;
extern double N0_forLaplacian;
extern double Lambda;
extern double collisionDistance, collisionDistance2;
extern double FluidDensity;

// 以下追加変数
extern double x_width, y_height, z_depth;   // 幅，高さ，奥行(流体領域)
extern double x_MAX, y_MAX, z_MAX;          // 計算領域の最大値:initilizeParticlePositionAndVelocity.cppで設定
extern double Pos_MIN[3];                   // 計算領域の最小値:struktBucketで設定
extern double DB, DB2, DBinv;               // バケット一辺の長さ，その二乗，逆数
extern int buckets;                         // バケットの総数，initilizationで定義，structBktで実装
extern int nBx, nBy, nBz, nBxy, nBxyz;      // x, y, z方向のバケット数とその積


#endif // INPUTS_HPP_20210220_220210_