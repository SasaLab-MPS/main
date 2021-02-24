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
double x_MAX = 1.0, y_MAX = 0.6, z_MAX = 0.3;   // 計算領域の最大値
double Pos_MIN[3] = {0, 0, 0};                  // 計算領域の最小値:struktBktで設定

// バケット構築のための変数
double DB, DB2, DBinv;                          // バケット一辺の長さ，その二乗，逆数
int nBx, nBy, nBz, nBxy, nBxyz;                 // x, y, z方向のバケット数とその積
double re, re2;                                 // 影響半径，影響半径の二乗


void initializeParticlePositionAndVelocity_for2dim(double wx, double hy)
{
    int i = 0;
    int iX, iY;
    int nX, nY;
    double ix, iy, iz;
    Position p;

    // cout << "*** call DIM 2 ***" << endl; :OK

    // 計算領域全体の大きさ1.0 m x 0.6 m
    nX = (int)(x_MAX / PARTICLE_DISTANCE) + 5;
    nY = (int)(y_MAX / PARTICLE_DISTANCE) + 5;

    //cout << "nX:" << nX << endl; :OK
    //cout << "nY:" << nY << endl; :OK
    //cout << "wX:" << wx << endl; :OK
    //cout << "hY:" << hy << endl; :OK

    for (iX = -4; iX < nX; iX++) // 計算領域下限から粒子生成
    {
        for (iY = -4; iY < nY; iY++)
        {
            ix = PARTICLE_DISTANCE * (double)(iX); // 粒子生成候補位置
            iy = PARTICLE_DISTANCE * (double)(iY);
            iz = 0.0;    // 奥行は0で設定
            
            // cout << "ix:" << ix << endl; : OK

            /* dummy wall region */
            if (((ix > -4.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((iy > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS)))
            {
                //p = {x, y, z, DUMMY_WALL};
                //position.push_back(p);
                continue;
            }

            /* wall region */
            if (((ix > -2.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((iy > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS)))
            {
                //p = {x, y, z, WALL};
                //position.push_back(p);
                continue;
            }

            /* wall region */
            if (((ix > -4.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((iy > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS)))
            {
                // p = {x, y, z, WALL};
                //position.push_back(p);
                continue;
            }

            /* empty region 粒子を生成しない */
            if (((ix > 0.0 + EPS) && (ix <= x_MAX + EPS)) && (iy > 0.0 + EPS))
            {
                continue;
            }

            /* fluid region：流体領域を設定 */
            if (((ix > 0.0 + EPS) && (ix <= wx + EPS)) && ((iy > 0.0 + EPS) && (iy <= hy + EPS)))
            {
                cout << "*** call FLUID region ***" << endl;
                p = {ix, iy, iz, FLUID};
                position.push_back(p);
                i++;
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

void initializeParticlePositionAndVelocity_for3dim(double wx, double hy, double dz)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double ix, iy, iz;
    int i = 0;
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
                ix = PARTICLE_DISTANCE * iX;
                iy = PARTICLE_DISTANCE * iY;
                iz = PARTICLE_DISTANCE * iZ;


                /* dummy wall region */
                if ((((ix > -4.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((iy > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS))) && ((iz > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (iz <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    //p = {x, y, z, DUMMY_WALL};
                    //position.push_back(p);
                    continue;
                }

                /* wall region */
                if ((((ix > -2.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((iy > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS))) && ((iz > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (iz <= z_MAX + 2.0 * PARTICLE_DISTANCE + EPS)))
                {
                    //p = {x, y, z, WALL};
                    //position.push_back(p);
                    continue;
                }

                /* wall region */
                if ((((ix > -4.0 * PARTICLE_DISTANCE + EPS) && (ix <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((iy > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (iy <= y_MAX + EPS))) && ((iz > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (iz <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    //p = {x, y, z, WALL};
                    //position.push_back(p);
                    continue;
                }

                /* empty region */
                if ((((ix > 0.0 + EPS) && (ix <= x_MAX + EPS)) && (iy > 0.0 + EPS)) && ((iz > 0.0 + EPS) && (iz <= z_MAX + EPS)))
                {
                    continue;
                }

                /* fluid region */
                if ((((ix > 0.0 + EPS) && (ix <= wx + EPS)) && ((iy > 0.0 + EPS) && (iy < hy + EPS))) && ((iz > 0.0 + EPS) && (iz <= dz + EPS)))
                {
                    p = {ix, iy, iz, FLUID};
                    position.push_back(p);
                    i++;
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