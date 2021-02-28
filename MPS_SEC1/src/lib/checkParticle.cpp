/*=====================================================================
  checkParticle.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算領域外に出た粒子を処理
  Last update: Feb 28, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void checkParticle(void) {
    double x_MIN, y_MIN, z_MIN;

    x_MIN = Pos_MIN[0] - PARTICLE_DISTANCE * 3;
    y_MIN = Pos_MIN[1] - PARTICLE_DISTANCE * 3;
    z_MIN = Pos_MIN[2] - PARTICLE_DISTANCE * 3;

    for(int i = 0; i < NumberOfParticles; i++) {
        if (position[i].x > x_MAX || position[i].x < x_MIN || position[i].y > y_MAX || position[i].y < y_MIN || position[i].z > z_MAX || position[i].z < z_MIN)
        {
            position[i].particleType = GHOST;
            pressure[i] = 0;
            velocity[i].x = 0;
            velocity[i].y = 0;
            velocity[i].z = 0;
        }
    }    
}