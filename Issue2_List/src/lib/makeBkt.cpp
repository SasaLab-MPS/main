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
    for(int i = 0; i < NumberOfParticles; i++) {
        if (ParticleType[i] == GHOST)
        {
            continue;
        }
        int ix = (int)((Position[i*3] - x_MIN) * DBinv) + 1;
        int iy = (int)((Position[i*3 + 1] - x_MIN) * DBinv) + 1;
        int iz = (int)((Position[i*3 + 2] - x_MIN) * DBinv) + 1;
        int id = iz * nBxy + iy *nBx + ix;
        bkt[id].push_back(i);
        Pid[i] = id;
    }
}