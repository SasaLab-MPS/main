/*=====================================================================
  calBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の所属するバケットを計算する関数
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void calBucket(void) {
    bucket.clear(); // 全てのバケットを粒子が無い状態に
    bucket.resize(buckets);
    double MIN[3];
    for (int i = 0; i < 3; i++) {
        MIN[i] = Pos_MIN[i] - PARTICLE_DISTANCE * 4;
    }

    for (int i = 0; i < NumberOfParticles; i++) {
        int ix = (int)((particle[i].x - MIN[0]) * DBinv) + 1;
        int iy = (int)((particle[i].y - MIN[1]) * DBinv) + 1;
        int iz = (int)((particle[i].z - MIN[2]) * DBinv) + 1;
        int id = iz * nBxy + iy * nBx + ix;

        bucket[id].emplace_back(i);
    }
}