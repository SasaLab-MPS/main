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
    int i, j;
    double xij, yij, zij;
    double distance, distance2;
    double forceDT; /* forceDT is the impulse of collision between particles */
    double mi, mj;
    double velocity_ix, velocity_iy, velocity_iz;
    double e = COEFFICIENT_OF_RESTITUTION;
    static vector<Velocity> VelocityAfterCollision;
    VelocityAfterCollision.resize(NumberOfParticles);

    for (i = 0; i < NumberOfParticles; i++)
    {
        VelocityAfterCollision[i].x = velocity[i].x;
        VelocityAfterCollision[i].y = velocity[i].y;
        VelocityAfterCollision[i].z = velocity[i].z;
    }

    calBkt(); // 粒子が所属するバケットを計算

    // 粒子同士の衝突を計算
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (position[i].particleType == FLUID)
        {
            mi = FluidDensity;
            // 粒子 iの速度
            velocity_ix = velocity[i].x;
            velocity_iz = velocity[i].y;
            velocity_iy = velocity[i].z;

            /* バケット法による粒子の探索効率向上 */
            // 粒子の所属するバケットのid
            int bktid[3]; // 0:x, 1:y, 2:z
            bktid[0] = (int)((position[i].x - Pos_MIN[0]) * DBinv) + 1;
            bktid[1] = (int)((position[i].y - Pos_MIN[1]) * DBinv) + 1;
            bktid[2] = (int)((position[i].z - Pos_MIN[2]) * DBinv) + 1;

            // 対象のバケット周辺の粒子のみを探索 3*3*3=27
            for (int jz = bktid[2] - 1; jz <= bktid[2] + 1; jz++) {
                for (int jy = bktid[1] - 1; jy <= bktid[1] + 1; jy++) {
                    for (int jx = bktid[0] - 1; jx <= bktid[0] + 1; jx++) {
                        // バケットのidを計算, 2次元のときnBxy = 0としている
                        int id = jz * nBxy + jy * nBx + jx;
                        if (bkt[id][0] == -1) // バケット内に粒子が存在しない
                        {
                            continue;
                        }
                        // バケット内の粒子と対象の粒子との粘性相互作用を計算
                        for (int j = 0; j < bkt[id].size(); j++)
                        {
                            int par_j = bkt[id][j]; // particle j
                            if ((par_j == i) || (position[par_j].particleType == GHOST))
                                continue; // その粒子自身とゴースト粒子は計算に含めない
                            // 粒子間距離の計算
                            xij = position[par_j].x - position[i].x;
                            yij = position[par_j].y - position[i].y;
                            zij = position[par_j].z - position[i].z;
                            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                            // 影響範囲内か？
                            if (distance2 < collisionDistance2)
                            {
                                distance = sqrt(distance2);
                                forceDT = (velocity_ix - velocity[par_j].x) * (xij / distance) + (velocity_iy - velocity[par_j].y) * (yij / distance) + (velocity_iz - velocity[par_j].z) * (zij / distance);
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
                    }
                }
            }
            VelocityAfterCollision[i].x = velocity_ix;
            VelocityAfterCollision[i].y = velocity_iy;
            VelocityAfterCollision[i].z = velocity_iz;
        }
    }

    // 速度の更新
    for (i = 0; i < NumberOfParticles; i++)
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