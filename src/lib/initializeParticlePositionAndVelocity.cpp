/*=====================================================================
  initializeParticlePositionAndVelocity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 10, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void initializeParticlePositionAndVelocity_for2dim(void)
{
    int iX, iY;
    int nX, nY;
    double x, y, z;
    int i = 0;
    int flagOfParticleGeneration;

    nX = (int)(1.0 / PARTICLE_DISTANCE) + 5;
    nY = (int)(0.6 / PARTICLE_DISTANCE) + 5;
    for (iX = -4; iX < nX; iX++)    // 計算領域下限から粒子生成
    {
        for (iY = -4; iY < nY; iY++)
        {
            x = PARTICLE_DISTANCE * (double)(iX);   // 粒子生成候補位置
            y = PARTICLE_DISTANCE * (double)(iY);
            z = 0.0;
            flagOfParticleGeneration = OFF;

            /* dummy wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS)))
            {
                ParticleType[i] = DUMMY_WALL;
                flagOfParticleGeneration = ON;
            }

            /* wall region */
            if (((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS)))
            {
                ParticleType[i] = WALL;
                flagOfParticleGeneration = ON;
            }

            /* wall region */
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= 1.00 + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.6 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= 0.6 + EPS)))
            {
                ParticleType[i] = WALL;
                flagOfParticleGeneration = ON;
            }

            /* empty region */
            if (((x > 0.0 + EPS) && (x <= 1.00 + EPS)) && (y > 0.0 + EPS))
            {
                flagOfParticleGeneration = OFF;
            }

            /* fluid region：流体領域か判定 */
            if (((x > 0.0 + EPS) && (x <= 0.25 + EPS)) && ((y > 0.0 + EPS) && (y <= 0.50 + EPS)))
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
    NumberOfParticles = i;
    for (i = 0; i < NumberOfParticles * 3; i++)
    {
        Velocity[i] = 0.0;
    }
}

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
