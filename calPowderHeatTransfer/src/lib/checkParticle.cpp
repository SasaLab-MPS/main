/*=====================================================================
  checkParticle.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算領域外に出た粒子を処理
  Last update: Feb 28, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

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
        if (particle[i].particleType != FLUID) {
            continue;
        }
        
        if (particle[i].x > x_max || particle[i].x < x_min || particle[i].y > y_max || particle[i].y < y_min || particle[i].z > z_max || particle[i].z < z_min)
        {
            particle[i].particleType = GHOST;
            pressure[i] = 0.0;
            velocity[i].x = 0.0;
            velocity[i].y = 0.0;
            velocity[i].z = 0.0;
        }
    }    
}