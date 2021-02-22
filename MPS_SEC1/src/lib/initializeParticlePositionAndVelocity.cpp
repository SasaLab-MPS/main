/*=====================================================================
  initializeParticlePositionAndVelocity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 20, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

/* 動的配列 */
vector<Position> position;                    // 位置
vector<Velocity> velocity;                    // 速度
vector<Acceleration> acceleration;            // 加速度
MatrixXd coefficientMatrix;                   // A:係数行列 = CoefficientMatrix
VectorXd sourceTerm, pressure;                // b:右辺係数，x:圧力の列ベクトル
vector<double> numberDensity;                 // 粒子密度，calNumberDensityで定義
vector<int> boundaryCondition;                // ディリクレ境界条件を付加するかどうかのフラグ
vector<int> flagForCheckingBoundaryCondition; // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ
vector<double> minimumPressure;               // ある粒子近傍での最低圧力
vector<vector<int>> bkt;                      // バケットid，structBktで定義
vector<int> Pid;                              // 粒子が所属するバケット番号
vector<int> neghPar;                          // 対象の粒子近傍の粒子リスト

/* グローバル変数定義 */
int FileNumber;
double Time;
int NumberOfParticles; // 全粒子数
double Re_forNumberDensity, Re2_forNumberDensity;
double Re_forGradient, Re2_forGradient;
double Re_forLaplacian, Re2_forLaplacian;       // Re:ラプラシアンモデルの影響範囲, calConstantParameterで設定
double N0_forNumberDensity;                     // 粒子数密度
double N0_forGradient;
double N0_forLaplacian;
double Lambda;
double collisionDistance, collisionDistance2;
double FluidDensity;
double x_width, y_height, z_depth;              // 幅，高さ，奥行(流体領域)
double x_MAX = 1.0, y_MAX = 0.6, z_MAX = 0.3;   // 計算領域の最大値:main.cppで設定
double Pos_MIN[3] = {0, 0, 0};                  // 計算領域の最小値:struktBktで設定

// バケット構築のための変数
double DB, DB2, DBinv;                          // バケット一辺の長さ，その二乗，逆数
int nBx, nBy, nBz, nBxy, nBxyz;                 // x, y, z方向のバケット数とその積
double re, re2;                                 // 影響半径，影響半径の二乗


void initializeParticlePositionAndVelocity_for2dim(double x_width, double y_height)
{
    int iX, iY;
    int nX, nY;
    double x, y, z;
    Position p;

    // 計算領域全体の大きさ1.0 m x 0.6 m
    nX = (int)(x_MAX / PARTICLE_DISTANCE) + 5;
    nY = (int)(y_MAX / PARTICLE_DISTANCE) + 5;
    for (iX = -4; iX < nX; iX++) // 計算領域下限から粒子生成
    {
        for (iY = -4; iY < nY; iY++)
        {
            x = PARTICLE_DISTANCE * (double)(iX); // 粒子生成候補位置
            y = PARTICLE_DISTANCE * (double)(iY);
            z = 0.0;    // 奥行は0で設定

            /* dummy wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                p = {x, y, z, DUMMY_WALL};
                position.push_back(p);
            }

            /* wall region */
            if (((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                p = {x, y, z, WALL};
                position.push_back(p);
            }

            /* wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                p = {x, y, z, WALL};
                position.push_back(p);
            }

            /* empty region 粒子を生成しない */
            if (((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS))
            {
                continue;
            }

            /* fluid region：流体領域を設定 */
            if (((x > 0.0 + EPS) && (x <= x_width + EPS)) && ((y > 0.0 + EPS) && (y <= y_height + EPS)))
            {
                p = {x, y, z, FLUID};
                position.push_back(p);
            }
        }
    }
    NumberOfParticles = position.size();
    cout << "*** NumberOfParticles = " << NumberOfParticles << " ***" << endl;
    // 速度，加速度を0で初期化
    p = {0, 0, 0, FLUID};
    velocity.resize(NumberOfParticles, p);
    acceleration.resize(NumberOfParticles);
}

void initializeParticlePositionAndVelocity_for3dim(double x_width, double y_height, double z_depth)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double x, y, z;
    int i = 0;
    int flagOfParticleGeneration;
    Position p;

    nX = (int)(x_MAX / PARTICLE_DISTANCE) + 5;
    nY = (int)(y_MAX / PARTICLE_DISTANCE) + 5;
    nZ = (int)(z_MAX / PARTICLE_DISTANCE) + 5;
    for (iX = -4; iX < nX; iX++)
    {
        for (iY = -4; iY < nY; iY++)
        {
            for (iZ = -4; iZ < nZ; iZ++)
            {
                x = PARTICLE_DISTANCE * iX;
                y = PARTICLE_DISTANCE * iY;
                z = PARTICLE_DISTANCE * iZ;
                flagOfParticleGeneration = OFF;

                /* dummy wall region */
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    p = {x, y, z, DUMMY_WALL};
                    position.push_back(p);
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 2.0 * PARTICLE_DISTANCE + EPS)))
                {
                    p = {x, y, z, WALL};
                    position.push_back(p);
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    p = {x, y, z, WALL};
                    position.push_back(p);
                    flagOfParticleGeneration = ON;
                }

                /* empty region */
                if ((((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS)) && ((z > 0.0 + EPS) && (z <= z_MAX + EPS)))
                {
                    flagOfParticleGeneration = OFF;
                }

                /* fluid region */
                if ((((x > 0.0 + EPS) && (x <= x_width + EPS)) && ((y > 0.0 + EPS) && (y < y_height + EPS))) && ((z > 0.0 + EPS) && (z <= z_depth + EPS)))
                {
                    p = {x, y, z, FLUID};
                    position.push_back(p);
                    flagOfParticleGeneration = ON;
                }
            }
        }
    }
    NumberOfParticles = i;
    cout << "*** NumberOfParticles = " << NumberOfParticles << " ***" << endl;
    // 速度，加速度を0で初期化
    p = {0, 0, 0, FLUID};
    velocity.resize(NumberOfParticles, p);
    acceleration.resize(NumberOfParticles);
}