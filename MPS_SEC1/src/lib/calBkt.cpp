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
    // 全てのバケットを-1:粒子が無い状態に
    fill(bkt.begin(), bkt.end(), -1);
    for(int i = 0; i < NumberOfParticles; i++) {
        if (position[i].particleType == GHOST)
        {
            continue;
        }
        int ix = (int)((position[i].x - Pos_MIN[0]) * DBinv) + 1;
        int iy = (int)((position[i].y - Pos_MIN[1]) * DBinv) + 1;
        int iz = (int)((position[i].z - Pos_MIN[2]) * DBinv) + 1;
        int id = iz * nBxy + iy *nBx + ix;

        if (bkt[id][0] == -1)   // そのバケットに入る初めての粒子の場合
        {
            bkt[id][0] = i;
        }
        else
        {
            bkt[id].push_back(i);
        }
    }
}