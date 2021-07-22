/*=====================================================================
  initializeParticlePositionAndVelocity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 20, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void initializeParticlePositionAndVelocity_for2dim(void)
{
    int iX, iY;
    int nX, nY;
    double x, y, z;
    int flagOfParticleGeneration;
    int ParticleType;
    int i = 0;
    Particle p;
    Velocity v;
    Acceleration a;

    // 計算領域全体の大きさ
    nX = (int)(x_MAX / PARTICLE_DISTANCE) + 5;
    nY = (int)(y_MAX / PARTICLE_DISTANCE) + 5;

    for (iX = -4; iX < nX; iX++) // 計算領域下限から粒子生成
    {
        for (iY = -4; iY < nY; iY++)
        {
            x = PARTICLE_DISTANCE * (double)(iX); // 粒子生成候補位置
            y = PARTICLE_DISTANCE * (double)(iY);
            z = 0.0;    // 厚みは0で設定
            flagOfParticleGeneration = OFF;
            
            /*
            // dummy wall region
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 4.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = DUMMY_WALL;
            }

            // wall region
            if (((x > -2.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 2.0 * PARTICLE_DISTANCE + EPS)) && ((y > 0.0 - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = WALL;
            }

            // wall region
            if (((x > -4.0 * PARTICLE_DISTANCE + EPS) && (x <= x_MAX + 4.0 * PARTICLE_DISTANCE + EPS)) && ((y > y_MAX - 2.0 * PARTICLE_DISTANCE + EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = WALL;
            }

            // empty region 粒子を生成しない
            if (((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS))
            {
                flagOfParticleGeneration = OFF;
            }
            */
            
            /* solid region：固体領域を設定 */
            if (((x > 0.0 - EPS) && (x <= x_MAX + EPS)) && ((y > 0.0 - EPS) && (y <= y_MAX + EPS)))
            {
                flagOfParticleGeneration = ON;
                ParticleType = SOLID;               
            }
            // 粒子の生成
            if (flagOfParticleGeneration == ON)
            {
                p = {x, y, z, ParticleType};
                // 速度，加速度を0で初期化
                v = {0.0, 0.0, 0.0};
                a = {0.0, 0.0, 0.0};
                // 追加
                particle.push_back(p);
                velocity.push_back(v);
                acceleration.push_back(a);
                i++;
            }
        }
    }

    NumberOfParticles = i;
    cout << "*** NumberOfParticles = " << NumberOfParticles << " ***" << endl;
}

void initializeParticlePositionAndVelocity_for3dim(void)
{
    int iX, iY, iZ;
    int nX, nY, nZ;
    double x, y, z;
    Particle p;
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
                /*
                if ((((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && (y > 0.0 + EPS)) && ((z > 0.0 + EPS) && (z <= z_MAX + EPS)))
                {
                    flagOfParticleGeneration = OFF;
                }
                */

                /* solid region */
                if ((((x > 0.0 + EPS) && (x <= x_MAX + EPS)) && ((y > 0.0 + EPS) && (y < y_MAX + EPS))) && ((z > 0.0 + EPS) && (z <= z_MAX + EPS)))
                {
                    flagOfParticleGeneration = ON;
                    ParticleType = SOLID;
                }

                if (flagOfParticleGeneration == ON)
                {
                    p = {x, y, z, ParticleType};
                    // 速度，加速度を0で初期化
                    v = {0, 0, 0};
                    a = {0, 0, 0};
                    // 追加
                    particle.push_back(p);
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