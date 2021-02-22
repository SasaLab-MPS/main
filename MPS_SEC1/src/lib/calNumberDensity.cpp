/*=====================================================================
  calNumberDensity.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子数密度を計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calNumberDensity(void)
{
    int i, j;
    double xij, yij, zij;
    double distance, distance2;
    double w;
    numberDensity.resize(NumberOfParticles);
    calBkt(); // 粒子が所属するバケットを計算

    for (i = 0; i < NumberOfParticles; i++)
    {
        numberDensity[i] = 0.0;
        if (position[i].particleType == GHOST)
            continue;

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
                    // バケット内の粒子と対象の粒子で計算
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
                        distance = sqrt(distance2);
                        // 重み関数の計算
                        w = weight(distance, Re_forNumberDensity);
                        numberDensity[i] += w;
                    }
                }
            }
        }
    }
}