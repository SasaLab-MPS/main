/*=====================================================================
  calBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の所属するバケットを計算する関数
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calBkt(void) {
    bkt.clear(); // 全てのバケットを粒子が無い状態に
    bkt.resize(bkts);
    double MIN[3];
    for (int i = 0; i < 3; i++) {
        MIN[i] = Pos_MIN[i] - PARTICLE_DISTANCE * 4;
    }

    for(int i = 0; i < NumberOfParticles; i++) {
        if (position[i].particleType == GHOST) {
            continue;
        }
        int ix = (int)((position[i].x - MIN[0]) * DBinv) + 1;
        int iy = (int)((position[i].y - MIN[1]) * DBinv) + 1;
        int iz = (int)((position[i].z - MIN[2]) * DBinv) + 1;
        int id = iz * nBxy + iy *nBx + ix;

        bkt[id].emplace_back(i);
    }
}