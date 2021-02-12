/*=====================================================================
  collision.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子を剛体とみなし粒子同士の異常接近を防止する
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void collision(void)
{
    int i, j;
    double xij, yij, zij;
    double distance, distance2;
    double forceDT; /* forceDT is the impulse of collision between particles */
    double mi, mj;
    double velocity_ix, velocity_iy, velocity_iz;
    double e = COEFFICIENT_OF_RESTITUTION;
    static double VelocityAfterCollision[3 * ARRAY_SIZE];

    for (i = 0; i < 3 * NumberOfParticles; i++)
    {
        VelocityAfterCollision[i] = Velocity[i];
    }
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == FLUID)
        {
            mi = FluidDensity;
            velocity_ix = Velocity[i * 3];
            velocity_iy = Velocity[i * 3 + 1];
            velocity_iz = Velocity[i * 3 + 2];
            for (j = 0; j < NumberOfParticles; j++)
            {
                if ((j == i) || (ParticleType[j] == GHOST))
                    continue;
                xij = Position[j * 3] - Position[i * 3];
                yij = Position[j * 3 + 1] - Position[i * 3 + 1];
                zij = Position[j * 3 + 2] - Position[i * 3 + 2];
                distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                if (distance2 < collisionDistance2)
                {
                    distance = sqrt(distance2);
                    forceDT = (velocity_ix - Velocity[j * 3]) * (xij / distance) + (velocity_iy - Velocity[j * 3 + 1]) * (yij / distance) + (velocity_iz - Velocity[j * 3 + 2]) * (zij / distance);
                    if (forceDT > 0.0)
                    {
                        mj = FluidDensity;
                        forceDT *= (1.0 + e) * mi * mj / (mi + mj);
                        velocity_ix -= (forceDT / mi) * (xij / distance);
                        velocity_iy -= (forceDT / mi) * (yij / distance);
                        velocity_iz -= (forceDT / mi) * (zij / distance);
                        /*
	    if(j>i){ fprintf(stderr,"WARNING: Collision occured between %d and %d particles.\n",i,j); }
	    */
                    }
                }
            }
            VelocityAfterCollision[i * 3] = velocity_ix;
            VelocityAfterCollision[i * 3 + 1] = velocity_iy;
            VelocityAfterCollision[i * 3 + 2] = velocity_iz;
        }
    }
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == FLUID)
        {
            Position[i * 3] += (VelocityAfterCollision[i * 3] - Velocity[i * 3]) * DT;
            Position[i * 3 + 1] += (VelocityAfterCollision[i * 3 + 1] - Velocity[i * 3 + 1]) * DT;
            Position[i * 3 + 2] += (VelocityAfterCollision[i * 3 + 2] - Velocity[i * 3 + 2]) * DT;
            Velocity[i * 3] = VelocityAfterCollision[i * 3];
            Velocity[i * 3 + 1] = VelocityAfterCollision[i * 3 + 1];
            Velocity[i * 3 + 2] = VelocityAfterCollision[i * 3 + 2];
        }
    }
}
