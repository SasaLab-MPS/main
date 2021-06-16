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
#include <Eigen/Sparse>
using namespace std;
using namespace Eigen;

/* 定数定義 */
/* for two-dimensional simulation */
constexpr int DIM = 2;                      // 次元
constexpr double PARTICLE_DISTANCE = 0.05;  // 初期粒子間距離 l0 (mm)
constexpr double DT = 50e-6;                // 時間刻み幅 (s)
constexpr int OUTPUT_INTERVAL = 20;         // 計算結果のファイル出力の間隔

/* for three-dimensional simulation */
/*
constexpr int DIM = 3;
constexpr double PARTICLE_DISTANCE = 0.075;
constexpr double DT = 0.003;
constexpr int OUTPUT_INTERVAL = 20;
*/

constexpr double FINISH_TIME = 0.010;                     // シミュレーションの終了時刻
constexpr double KINEMATIC_VISCOSITY = 1.0e-6;            // 動粘性係数
constexpr double FLUID_DENSITY = 0.0027;                  // 流体の密度:ρ_f (g/mm^3)
constexpr double SOLID_DENSITY = 0.008;                   // 固体の密度:ρ_s (g/mm^3)
constexpr double G_X = 0.0;
constexpr double G_Y = -9.8;                              // 重力加速度 (m/s^2)
constexpr double G_Z = 0.0;
constexpr double RADIUS_FOR_NUMBER_DENSITY = (2.1 * PARTICLE_DISTANCE);
constexpr double RADIUS_FOR_GRADIENT = (2.1 * PARTICLE_DISTANCE);
constexpr double RADIUS_FOR_LAPLACIAN = (3.1 * PARTICLE_DISTANCE);
constexpr double COLLISION_DISTANCE = (0.5 * PARTICLE_DISTANCE);
constexpr double THRESHOLD_RATIO_OF_NUMBER_DENSITY = 0.90; // 自由表面かを判定する係数β
constexpr double COEFFICIENT_OF_RESTITUTION = 0.2;         // 剛体衝突の反発係数
constexpr double COMPRESSIBILITY = 0.45e-9;                // 流体の圧縮率
constexpr double EPS = (0.01 * PARTICLE_DISTANCE);         // 粒子間隔の100分の1を誤差の判定に利用
constexpr double cgEPS = 1.0e-8;                           // CG法で許容する誤差の上限
constexpr int ON = 1;
constexpr int OFF = 0;
constexpr double RELAXATION_COEFFICIENT_FOR_PRESSURE = 0.2; // 計算を安定させるための緩和係数
/* 粒子ID */
constexpr int GHOST = -1;                                   // 計算に関与しない粒子
constexpr int SOLID = 0;                                    // 個体粒子
constexpr int FLUID = 1;                                    // 流体粒子
constexpr int GAS = 2;                                      // 気体粒子
constexpr int POWDER = 3;                                   // 粉末粒子
constexpr int PHOTON = 4;                                   // 光子
constexpr int WALL = 12;                                    // (圧力は計算せず，粒子数密度の計算は行う)壁粒子
constexpr int DUMMY_WALL = 13;                              // 仮想的な壁
constexpr int GHOST_OR_DUMMY = -1;                          // ポアソン方程式の計算時に用いる
constexpr int SURFACE_PARTICLE = 1;                         // (圧力を計算する)壁粒子, 最表面の粒子
constexpr int INNER_PARTICLE = 0;                           // 流体内部の粒子
/* 境界条件 */
constexpr int DIRICHLET_BOUNDARY_IS_NOT_CONNECTED = 0;      // ディリクレ条件が設定されていない
constexpr int DIRICHLET_BOUNDARY_IS_CONNECTED = 1;          // ディリクレ条件を設定済み
constexpr int DIRICHLET_BOUNDARY_IS_CHECKED = 2;            // ディリクレ条件を満たすことを確認済み
constexpr double CRT_NUM = 0.1;                             // クーラン数

/* 熱伝導係数等 */
constexpr double SPECIFIC_HEAT_CAPACITY = 500;              // 比熱容量:c (mJ/gK)
constexpr double HEAT_CONDUCTIVITY = 300;                   // 熱伝導率:λ (mJ/mmKs)
constexpr double LASER_ABSORPTION_RATE = 0.20;              // レーザ吸収率(アルミ)
/* 初期温度・融点・沸点等 */
constexpr double INITIAL_TEMPERATURE = 20.0;                // 初期温度 (℃)
constexpr double MELTING_TEMPERATURE = 660;                 // 融点:Tm (℃)
constexpr double BOILING_TEMPERATURE = 2520;                // 沸点:Tb (℃)
constexpr double LATENT_HEAT = 396.0;                       // 潜熱:L (J/g)
/* 走査パターン */
constexpr int SINGLE = 0;                                   // シングルスキャン
constexpr int ISLAND = 1;                                   // アイランドスキャン
constexpr int STRIPE = 2;                                   // ストライプスキャン
/* レーザ諸元・造形条件*/
constexpr double HEAT_INPUT = 100;                          // 初期熱量:Q (mJ/mm^2)
constexpr double LASER_POWER = 3e2;                         // レーザ出力:P (W, J/s)
constexpr double LASER_DIAMETER = 0.1;                      // レーザ直径:d (mm)
constexpr double SCAN_SPEED = 1e3;                          // レーザ走査速度:v (mm/s)
constexpr double SCAN_PITCH = 0.1;                          // 走査ピッチ:h (mm)
constexpr double SCAN_VECTOR_LENGTH = 1.0;                  // 走査ベクトル長さ (mm)
/* 表面張力定数 */
constexpr double SIGMA = 0.000878;                          // 表面張力係数:σ (N/mm)
/* ブシネスク近似 */
constexpr double LINEAR_EXPANSION_COEFFICIENT = 23.9e-6;    // 線膨張係数:α (1/℃) 


/* 粒子の座標，速度，速度を表す構造体 */
// 座標:Position，粒子の状態を持つ
typedef struct {
  double x;
  double y;
  double z;
  int particleType; // 粒子の状態
} Particle;
// 座標
typedef struct {
  double x;
  double y;
  double z;
} Coordinate;

typedef Coordinate Velocity;                            // 速度:Velocity
typedef Coordinate Acceleration;                        // 加速度:Acceleration
typedef Coordinate Force;                               // 力：Force
typedef Triplet<double> Tri;                            // Tripletの省略

/* ---位置・速度・加速度--- */
extern vector<Particle> particle;                       // 位置
extern vector<Velocity> velocity;                       // 速度
extern vector<Acceleration> acceleration;               // 加速度
/* ---圧力計算--- */
extern SparseMatrix<double> coefficientMatrix;          // CoefficientMatrix: mianLoopで定義
extern vector<Tri> P_aij;                               // A:係数行列(疎行列)
extern VectorXd sourceTerm, pressure;                   // b:右辺係数，x:圧力の列ベクトル
extern vector<double> numberDensity;                    // 粒子密度
extern vector<int> boundaryCondition;                   // ディリクレ境界条件を付加するかどうかのフラグ
extern vector<int> flagForCheckingBoundaryCondition;    // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ
extern vector<double> minimumPressure;                  // ある粒子近傍での最低圧力
/* ---温度計算--- */
extern vector<Tri> T_aij;                               // トリプレット
extern SparseMatrix<double> Tmp;                        // 係数行列(疎行列)                               // A:係数行列(疎行列)
extern VectorXd temperature;                            // 確定している温度，temperature:温度の列ベクトル
extern Coordinate centerOfLaser;                        // レーザ照射の中心座標
extern vector<int> NeumannBoundaryCondition;            // ノイマン境界条件
/* ---表面張力計算--- */
extern vector<Coordinate> normalVector;                 // 単位法線ベクトル
extern vector<Force> surfaceTension;                    // 表面張力
/* ---バケット法--- */
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
extern double N0_forSurfaceTension;
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