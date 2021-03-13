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
// constantParameterで定義
MatrixXd coefficientMatrix;                   // A:係数行列 = CoefficientMatrix
VectorXd sourceTerm, pressure;                // b:右辺係数，x:圧力の列ベクトル
vector<double> numberDensity;                 // 粒子密度
// 境界条件に関わる変数
vector<int> boundaryCondition;                // ディリクレ境界条件を付加するかどうかのフラグ
vector<int> flagForCheckingBoundaryCondition; // 粒子の集合のどこかにディリクレ境界条件が付加されているかをチェックするためのフラグ
vector<double> minimumPressure;               // ある粒子近傍での最低圧力

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
double x_MAX = 1.0, y_MAX = 0.6, z_MAX = 0.3;   // 計算領域の最大値
double Pos_MIN[3] = {0.0, 0.0, 0.0};            // 計算領域の最小値:struktBktで設定

// バケット探索法に関わる変数・配列
vector<vector<int>> bkt;                        // バケットid，structBktで定義
vector<int> neghPar;                            // 対象の粒子近傍の粒子リスト
double DB, DB2, DBinv;                          // バケット一辺の長さ，その二乗，逆数
int bkts;                                       // バケットの総数
int nBx, nBy, nBz, nBxy, nBxyz;                 // x, y, z方向のバケット数とその積


void initializeParticlePositionAndVelocity_for2dim(double wx, double hy)
{
    int iX, iY;
    int nX, nY;
    double x, y, z;
    int flagOfParticleGeneration;
    int ParticleType;
    int i = 0;
    Position p;
    Velocity v;
    Acceleration a;

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
            flagOfParticleGeneration = OFF;

            /* dummy wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = DUMMY_WALL;
            }

            /* wall region */
            if (((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = WALL;
            }

            /* wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = WALL;
            }

            /* empty region 粒子を生成しない */
            if (((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS))
            {
                flagOfParticleGeneration = OFF;
            }

            /* fluid region：流体領域を設定 */
            if (((x > 0.0 + EPS) && (x <= wx + EPS)) && ((y > 0.0 + EPS) && (y <= hy + EPS)))
            {
                //cout << "*** make FLUID region ***" << endl; :OK
                flagOfParticleGeneration = ON;
                ParticleType = FLUID;               
            }
            // 粒子の生成
            if (flagOfParticleGeneration == ON)
            {
                p = {x, y, z, ParticleType};
                // 速度，加速度を0で初期化
                v = {0.0, 0.0, 0.0, ParticleType};
                a = {0.0, 0.0, 0.0, ParticleType};
                // 追加
                position.push_back(p);
                velocity.push_back(v);
                acceleration.push_back(a);
                i++;
            }
        }
    }

    NumberOfParticles = i;
    cout << "*** NumberOfParticles = " << NumberOfParticles << " ***" << endl;
}

void initializeParticlePositionAndVelocity_for3dim(double wx, double hy, double dz)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double x, y, z;
    Position p;
    Velocity v;
    Acceleration a;
    int flagOfParticleGeneration;
    int ParticleType;
    int i = 0;

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
                    flagOfParticleGeneration = ON;
                    ParticleType = DUMMY_WALL;
                }

                /* wall region */
                if ((((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 2.0 * PARTICLE_DISTANCE + EPS)))
                {
                    flagOfParticleGeneration = ON;
                    ParticleType = WALL;
                }

                /* wall region */
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    flagOfParticleGeneration = ON;
                    ParticleType = WALL;
                }

                /* empty region */
                if ((((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS)) && ((z > 0.0 + EPS) && (z <= z_MAX + EPS)))
                {
                    flagOfParticleGeneration = OFF;
                }

                /* fluid region */
                if ((((x > 0.0 + EPS) && (x <= wx + EPS)) && ((y > 0.0 + EPS) && (y < hy + EPS))) && ((z > 0.0 + EPS) && (z <= dz + EPS)))
                {
                    flagOfParticleGeneration = ON;
                    ParticleType = FLUID;
                }

                if (flagOfParticleGeneration == ON)
                {
                    p = {x, y, z, ParticleType};
                    // 速度，加速度を0で初期化
                    v = {0, 0, 0, ParticleType};
                    a = {0, 0, 0, ParticleType};
                    // 追加
                    position.push_back(p);
                    velocity.push_back(v);
                    acceleration.push_back(a);
                    i++;
                }
            }
        }
    }

    NumberOfParticles = i;
    cout << "*** NumberOfParticles = " << NumberOfParticles << " ***" << endl;
}