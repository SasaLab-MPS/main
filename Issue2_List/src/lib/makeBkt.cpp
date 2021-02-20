/*=====================================================================
  makeBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  バケットに粒子を格納する関数
  Last update: Feb 19, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void makeBkt(void) {
    // 全てのバケットを-1:粒子が無い状態に
    fill(bkt.begin(), bkt.end(), -1);
    fill(Pid.begin(), Pid.end(), -1);
    for(int i = 0; i < NumberOfParticles; i++) {
        if (ParticleType[i] == GHOST)
        {
            continue;
        }
        int ix = (int)((Position[i*3] - Pos_MIN[0]) * DBinv) + 1;
        int iy = (int)((Position[i*3 + 1] - Pos_MIN[1]) * DBinv) + 1;
        int iz = (int)((Position[i*3 + 2] - Pos_MIN[2]) * DBinv) + 1;
        int id = iz * nBxy + iy *nBx + ix;
        Pid[i] = id;    // その粒子が所属するバケットのid

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