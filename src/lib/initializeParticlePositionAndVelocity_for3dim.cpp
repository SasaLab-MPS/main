/*=====================================================================
  initializeParticlePositionAndVelocity_for3dim.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  三次元での計算を始める前の初期化
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

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

void initializeParticlePositionAndVelocity_for3dim(void)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double x, y, z;
    int i = 0;
    int flagOfParticleGeneration;

    nX = (int)(1.0 / PARTICLE_DISTANCE) + 5;
    nY = (int)(0.6 / PARTICLE_DISTANCE) + 5;
    nZ = (int)(0.3 / PARTICLE_DISTANCE) + 5;
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
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= 0.3 + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    ParticleType[i] = DUMMY_WALL;
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS))) && ((z > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (z <= 0.3 + 2.0 * PARTICLE_DISTANCE + EPS)))
                {
                    ParticleType[i] = WALL;
                    flagOfParticleGeneration = ON;
                }

                /* wall region */
                if ((((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.6 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS))) && ((z > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (z <= 0.3 + 4.0 * PARTICLE_DISTANCE + EPS)))
                {
                    ParticleType[i] = WALL;
                    flagOfParticleGeneration = ON;
                }

                /* empty region */
                if ((((x > 0.0 + EPS) && (x <= 1.00 + EPS)) && (y > 0.0 + EPS)) && ((z > 0.0 + EPS) && (z <= 0.3 + EPS)))
                {
                    flagOfParticleGeneration = OFF;
                }

                /* fluid region */
                if ((((x > 0.0 + EPS) && (x <= 0.25 + EPS)) && ((y > 0.0 + EPS) && (y < 0.5 + EPS))) && ((z > 0.0 + EPS) && (z <= 0.3 + EPS)))
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
