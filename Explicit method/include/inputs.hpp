/*=====================================================================
  constants.hpp   
  Yota INOUE (2021) 
  粒子法プログラムの定数定義ファイル
  Last update: Feb 10, 2021
=======================================================================*/
//#include "inputs.hpp"
#ifndef INPUTS_HPP_20210211_200210_
#define INPUTS_HPP_20210211_200210_

#include <bits/stdc++.h>
using namespace std;

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

#define ARRAY_SIZE 5000 // 粒子数の上限
#define FINISH_TIME 2.0 // シミュレーションの終了時刻
#define KINEMATIC_VISCOSITY (1.0E-6)
#define FLUID_DENSITY 1000.0
#define G_X 0.0
#define G_Y -9.8
#define G_Z 0.0
#define RADIUS_FOR_NUMBER_DENSITY (2.1 * PARTICLE_DISTANCE)
#define RADIUS_FOR_GRADIENT (2.1 * PARTICLE_DISTANCE)
#define RADIUS_FOR_LAPLACIAN (3.1 * PARTICLE_DISTANCE)
#define COLLISION_DISTANCE (0.5 * PARTICLE_DISTANCE)
#define THRESHOLD_RATIO_OF_NUMBER_DENSITY 0.97
#define COEFFICIENT_OF_RESTITUTION 0.2
#define COMPRESSIBILITY (0.45E-9)
#define EPS (0.01 * PARTICLE_DISTANCE)  // 粒子間隔の100分の1を誤差の判定に利用
#define ON 1
#define OFF 0
#define RELAXATION_COEFFICIENT_FOR_PRESSURE 0.2     // 計算を安定させるための緩和係数
#define GHOST -1            // 計算に関与しない粒子
#define FLUID 0             // 流体粒子
#define WALL 2              // (圧力は計算せず，粒子数密度の計算は行う)壁粒子
#define DUMMY_WALL 3        // 
#define GHOST_OR_DUMMY -1   // ポアソン方程式の計算時に用いる 
#define SURFACE_PARTICLE 1  // (圧力を計算する)壁粒子
#define INNER_PARTICLE 0
#define DIRICHLET_BOUNDARY_IS_NOT_CONNECTED 0
#define DIRICHLET_BOUNDARY_IS_CONNECTED 1
#define DIRICHLET_BOUNDARY_IS_CHECKED 2

/* 配列宣言 */
extern double Acceleration[3 * ARRAY_SIZE];                 // 加速度
extern int ParticleType[ARRAY_SIZE];                        // 粒子のタイプ
extern double Position[3 * ARRAY_SIZE];                     // 位置
extern double Velocity[3 * ARRAY_SIZE];                     // 速度
extern double Pressure[ARRAY_SIZE];                         // 圧力
extern double NumberDensity[ARRAY_SIZE];                    // 粒子密度
extern int BoundaryCondition[ARRAY_SIZE];                   // 境界条件
extern double SourceTerm[ARRAY_SIZE];                       // ソースターム行列
extern int FlagForCheckingBoundaryCondition[ARRAY_SIZE];
extern double CoefficientMatrix[ARRAY_SIZE * ARRAY_SIZE];   // 係数行列A
extern double MinimumPressure[ARRAY_SIZE];                  // ある粒子近傍での最低圧力

/* 変数定義 */
extern int FileNumber;
extern double Time;
extern int NumberOfParticles;         // 全粒子数
extern double Re_forNumberDensity, Re2_forNumberDensity;
extern double Re_forGradient, Re2_forGradient;
extern double Re_forLaplacian, Re2_forLaplacian;
extern double N0_forNumberDensity;    // 粒子数密度
extern double N0_forGradient;
extern double N0_forLaplacian;
extern double Lambda;
extern double collisionDistance, collisionDistance2;
extern double FluidDensity;

#endif // INPUTS_HPP_20210211_200210_