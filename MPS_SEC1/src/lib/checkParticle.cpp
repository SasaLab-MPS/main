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
    double x_max, y_max, z_max;
    double x_min, y_min, z_min;

    x_max = x_MAX + PARTICLE_DISTANCE * 4;
    y_max = y_MAX + PARTICLE_DISTANCE * 4;
    z_max = z_MAX + PARTICLE_DISTANCE * 4;

    x_min = Pos_MIN[0] - PARTICLE_DISTANCE * 4;
    y_min = Pos_MIN[1] - PARTICLE_DISTANCE * 4;
    z_min = Pos_MIN[2] - PARTICLE_DISTANCE * 4;

    for(int i = 0; i < NumberOfParticles; i++) {
        if (position[i].x > x_max || position[i].x < x_min || position[i].y > y_max || position[i].y < y_min || position[i].z > z_max || position[i].z < z_min)
        {
            position[i].particleType = GHOST;
            pressure[i] = 0.0;
            velocity[i].x = 0.0;
            velocity[i].y = 0.0;
            velocity[i].z = 0.0;
        }
    }    
}