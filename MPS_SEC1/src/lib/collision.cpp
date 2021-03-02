/*=====================================================================
  collision.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子を剛体とみなし粒子同士の異常接近を防止する
  Last update: Feb 21, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void collision(void)
{
    double xij, yij, zij;
    double distance, distance2;
    double forceDT; /* forceDT is the impulse of collision between particles */
    double mi, mj;
    double velocity_ix, velocity_iy, velocity_iz;
    double e = COEFFICIENT_OF_RESTITUTION;
    vector<Velocity> VelocityAfterCollision;
    
    VelocityAfterCollision.resize(NumberOfParticles);

    // 更新前の速度を設定
    for (int i = 0; i < NumberOfParticles; i++)
    {
        VelocityAfterCollision[i].x = velocity[i].x;
        VelocityAfterCollision[i].y = velocity[i].y;
        VelocityAfterCollision[i].z = velocity[i].z;
    }

    calBkt(); // 粒子が所属するバケットを計算

    // 粒子同士の衝突を計算
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType == FLUID)
        {
            mi = FluidDensity;
            // 粒子 iの速度
            velocity_ix = velocity[i].x;
            velocity_iy = velocity[i].y;
            velocity_iz = velocity[i].z;

            /* バケット法による粒子の探索効率向上 */
            searchBkt(i);   // 粒子i近傍の粒子をneghParにリスト化
            int j;          // particle j
            for(int k = 0; k < (int)neghPar.size(); k++) {
                j = neghPar[k];
                if ((j == i) || (position[j].particleType == GHOST))
                    continue; // その粒子自身とゴースト粒子は計算に含めない
                // 粒子間距離の計算
                xij = position[j].x - position[i].x;
                yij = position[j].y - position[i].y;
                zij = position[j].z - position[i].z;
                distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                // 影響範囲内か？
                if (distance2 < collisionDistance2)
                {
                    distance = sqrt(distance2);
                    forceDT = (velocity_ix - velocity[j].x) * (xij / distance) + (velocity_iy - velocity[j].y) * (yij / distance) + (velocity_iz - velocity[j].z) * (zij / distance);
                    if (forceDT > 0.0)
                    {
                        mj = FluidDensity;
                        forceDT *= (1.0 + e) * mi * mj / (mi + mj);
                        velocity_ix -= (forceDT / mi) * (xij / distance);
                        velocity_iy -= (forceDT / mi) * (yij / distance);
                        velocity_iz -= (forceDT / mi) * (zij / distance);
                    }
                }
            }
            VelocityAfterCollision[i].x = velocity_ix;
            VelocityAfterCollision[i].y = velocity_iy;
            VelocityAfterCollision[i].z = velocity_iz;
        }
    }

    // 速度の更新
    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType == FLUID)
        {
            position[i].x += (VelocityAfterCollision[i].x - velocity[i].x) * DT;
            position[i].y += (VelocityAfterCollision[i].y - velocity[i].y) * DT;
            position[i].z += (VelocityAfterCollision[i].z - velocity[i].z) * DT;
            velocity[i].x = VelocityAfterCollision[i].x;
            velocity[i].y = VelocityAfterCollision[i].y;
            velocity[i].z = VelocityAfterCollision[i].z;
        }
    }
}