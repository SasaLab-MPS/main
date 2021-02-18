/*=====================================================================
  initializeParticlePositionAndVelocity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 10, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double Acceleration[3 * ARRAY_SIZE]; // 加速度
int ParticleType[ARRAY_SIZE];        // 粒子のタイプ
double Position[3 * ARRAY_SIZE];     // 位置
double Velocity[3 * ARRAY_SIZE];     // 速度
double Pressure[ARRAY_SIZE];         // 圧力
double NumberDensity[ARRAY_SIZE];    // 粒子密度
int BoundaryCondition[ARRAY_SIZE];   // 境界条件
double SourceTerm[ARRAY_SIZE];       // ソースターム行列
int FlagForCheckingBoundaryCondition[ARRAY_SIZE];
double CoefficientMatrix[ARRAY_SIZE * ARRAY_SIZE]; // 係数行列A
double MinimumPressure[ARRAY_SIZE];                // ある粒子近傍の最小圧力

int FileNumber;
double Time;
int NumberOfParticles; // 全粒子数
double Re_forNumberDensity, Re2_forNumberDensity;
double Re_forGradient, Re2_forGradient;
double Re_forLaplacian, Re2_forLaplacian;
double N0_forNumberDensity; // 粒子数密度
double N0_forGradient;
double N0_forLaplacian;
double Lambda;
double collisionDistance, collisionDistance2;
double FluidDensity;

// 領域の最大値
double x_MAX = 1.0, y_MAX = 0.6, z_MAX = 0.3;

void initializeParticlePositionAndVelocity_for2dim(double x_width, double y_height)
{
    int iX, iY;
    int nX, nY;
    double x, y, z;
    int i = 0;
    int flagOfParticleGeneration;

    // 計算領域全体の大きさ1.0 m x 0.6 m
    nX = (int)(x_MAX / PARTICLE_DISTANCE) + 5;
    nY = (int)(y_MAX / PARTICLE_DISTANCE) + 5;
    for (iX = -4; iX < nX; iX++)    // 計算領域下限から粒子生成
    {
        for (iY = -4; iY < nY; iY++)
        {
            x = PARTICLE_DISTANCE * (double)(iX);   // 粒子生成候補位置
            y = PARTICLE_DISTANCE * (double)(iY);
            z = 0.0;
            flagOfParticleGeneration = OFF;         // flagをリセット

            /* dummy wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                ParticleType[i] = DUMMY_WALL;
                flagOfParticleGeneration = ON;
            }

            /* wall region */
            if (((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                ParticleType[i] = WALL;
                flagOfParticleGeneration = ON;
            }

            /* wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                ParticleType[i] = WALL;
                flagOfParticleGeneration = ON;
            }

            /* empty region */
            if (((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS))
            {
                flagOfParticleGeneration = OFF;
            }

            /* fluid region：流体領域を設定 */
            if (((x > 0.0 + EPS) && (x <= x_width + EPS)) && ((y > 0.0 + EPS) && (y <= y_height + EPS)))
            {
                ParticleType[i] = FLUID;
                flagOfParticleGeneration = ON;
            }
            // 流体粒子である
            if (flagOfParticleGeneration == ON)
            {
                Position[i * 3] = x;
                Position[i * 3 + 1] = y;
                Position[i * 3 + 2] = z;
                i++;
            }
        }
    }
    NumberOfParticles = i;
    for (i = 0; i < NumberOfParticles * 3; i++)
    {
        Velocity[i] = 0.0;
    }
}

void initializeParticlePositionAndVelocity_for3dim(double x_width, double y_height, double z_depth)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double x, y, z;
    int i = 0;
    int flagOfParticleGeneration;

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
                    ParticleType[i] = DUMMY_WALL;
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 2.0 * PARTICLE_DISTANCE + EPS)))
                {
                    ParticleType[i] = WALL;
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= z_MAX + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    ParticleType[i] = WALL;
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
                    ParticleType[i] = FLUID;
                    flagOfParticleGeneration = ON;
                }

                if (flagOfParticleGeneration == ON)
                {
                    Position[i * 3] = x;
                    Position[i * 3 + 1] = y;
                    Position[i * 3 + 2] = z;
                    i++;
                }
            }
        }
    }
    NumberOfParticles = i;
    for (i = 0; i < NumberOfParticles * 3; i++)
    {
        Velocity[i] = 0.0;
    }
}
