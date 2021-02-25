/*=====================================================================
  inputs.hpp   
  Yota INOUE (2021) 
  粒子法プログラムの定数定義ファイル
  Last update: Feb 20, 2021
=======================================================================*/
//#include "inputs.hpp"
#ifndef INPUTS_HPP_20210220_220210_
#define INPUTS_HPP_20210220_220210_

#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

/* 変数予約 */
#define DIM 2                   // 次元
#define PARTICLE_DISTANCE 0.025 // 初期粒子間距離 l0
#define DT 0.001                // 時間刻み幅
#define OUTPUT_INTERVAL 20      // 計算結果のファイル出力の間隔

/* for three-dimensional simulation */
/*
#define DIM                  3
#define PARTICLE_DISTANCE    0.075
#define DT                   0.003
#define OUTPUT_INTERVAL      2 
*/

#define ARRAY_SIZE 5000              // 粒子数の上限
#define FINISH_TIME 2.0              // シミュレーションの終了時刻
#define KINEMATIC_VISCOSITY (1.0E-6) // 動粘性係数
#define FLUID_DENSITY 1000.0
#define G_X 0.0
#define G_Y -9.8 // 重力加速度
#define G_Z 0.0
#define RADIUS_FOR_NUMBER_DENSITY (2.1 * PARTICLE_DISTANCE)
#define RADIUS_FOR_GRADIENT (2.1 * PARTICLE_DISTANCE)
#define RADIUS_FOR_LAPLACIAN (3.1 * PARTICLE_DISTANCE)
#define COLLISION_DISTANCE (0.5 * PARTICLE_DISTANCE)
#define THRESHOLD_RATIO_OF_NUMBER_DENSITY 0.97 // 自由表面かを判定する係数β
#define COEFFICIENT_OF_RESTITUTION 0.2         // 剛体衝突の反発係数
#define COMPRESSIBILITY (0.45E-9)              // 流体の圧縮率
#define EPS (0.01 * PARTICLE_DISTANCE)         // 粒子間隔の100分の1を誤差の判定に利用
#define cgEPS 1.0e-8                           // CG法で許容する誤差の上限
#define ON 1
#define OFF 0
#define RELAXATION_COEFFICIENT_FOR_PRESSURE 0.2 // 計算を安定させるための緩和係数
#define GHOST -1                                // 計算に関与しない粒子
#define FLUID 0                                 // 流体粒子
#define WALL 2                                  // (圧力は計算せず，粒子数密度の計算は行う)壁粒子
#define DUMMY_WALL 3                            //
#define GHOST_OR_DUMMY -1                       // ポアソン方程式の計算時に用いる
#define SURFACE_PARTICLE 1                      // (圧力を計算する)壁粒子
#define INNER_PARTICLE 0
#define DIRICHLET_BOUNDARY_IS_NOT_CONNECTED 0
#define DIRICHLET_BOUNDARY_IS_CONNECTED 1
#define DIRICHLET_BOUNDARY_IS_CHECKED 2
#define CRT_NUM 0.1 // クーラン数

/* 粒子の座標，速度，速度を表す構造体 */
// 座標:Position
typedef struct {
    double x;
    double y;
    double z;
    int particleType;   // 粒子の状態も持つ
} Position;
// 速度:Velocity
typedef Position Velocity;
// 加速度:Acceleration
typedef Position Acceleration;

/* 動的配列 */
extern vector<Position> position;                       // 位置
extern vector<Velocity> velocity;                       // 速度
extern vector<Acceleration> acceleration;               // 加速度
extern MatrixXd coefficientMatrix;                      // A:係数行列 = CoefficientMatrix mianLoopで定義
extern VectorXd sourceTerm, pressure;                   // b:右辺係数，x:圧力の列ベクトル
extern vector<double> numberDensity;                    // 粒子密度
extern vector<int> boundaryCondition;                   // ディリクレ境界条件を付加するかどうかのフラグ
extern vector<int> flagForCheckingBoundaryCondition;    // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ
extern vector<double> minimumPressure;                  // ある粒子近傍での最低圧力
extern vector<vector<int>> bkt;                         // バケットid，structBktで定義
extern vector<int> neghPar;                             // 対象の粒子近傍の粒子, initilizationで定義

/* グローバル変数定義 */
extern int FileNumber;
extern double Time;
extern int NumberOfParticles; // 全粒子数
extern double Re_forNumberDensity, Re2_forNumberDensity;
extern double Re_forGradient, Re2_forGradient;
extern double Re_forLaplacian, Re2_forLaplacian; // Re:ラプラシアンモデルの影響範囲, calConstantParameterで設定
extern double N0_forNumberDensity;               // 粒子数密度
extern double N0_forGradient;
extern double N0_forLaplacian;
extern double Lambda;
extern double collisionDistance, collisionDistance2;
extern double FluidDensity;
// 以下追加変数
extern double x_width, y_height, z_depth;   // 幅，高さ，奥行(流体領域)
extern double x_MAX, y_MAX, z_MAX;          // 計算領域の最大値:main.cppで設定
extern double Pos_MIN[3];                   // 計算領域の最小値:struktBktで設定
// バケット構築のための変数
extern double DB, DB2, DBinv;               // バケット一辺の長さ，その二乗，逆数
extern int bkts;                            // バケットの総数，initilizationで定義
extern int nBx, nBy, nBz, nBxy, nBxyz;      // x, y, z方向のバケット数とその積
extern double re, re2;                      // 影響半径，影響半径の二乗


#endif // INPUTS_HPP_20210220_220210_