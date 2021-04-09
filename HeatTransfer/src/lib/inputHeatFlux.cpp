/*=====================================================================
  inputHeatFlux.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱流束を与える
  Last update: Mar 15, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void inputHeatFlux(void) {
  double area = M_PI * 0.25 * (LASER_DIAMETER * LASER_DIAMETER);
  double Q = LASER_POWER / area;   // W/mm^2 = J/mm^2
  double travelDistance = SCAN_SPEED * Time;

  // レーザの中心, zの座標は要検討
  Position center;
  center.x = travelDistance, center.y = y_MAX * 0.5, center.z = z_MAX;
  

  for(int i = 0; i < NumberOfParticles; i++) {
    heatFlux[i] = 0.0;
    if (DIM == 2)
    {
      double distance2 = (position[i].x - center.x) * (position[i].x - center.x) + (position[i].y - center.y) * (position[i].y - center.y);
      double distance = sqrt(distance2);
      if (distance < LASER_DIAMETER * 0.5 + EPS) {
        heatFlux[i] = Q;
      }     
    }
    else
    {
      double distance2 = (position[i].x - center.x) * (position[i].x - center.x) + (position[i].y - center.y) * (position[i].y - center.y) + (position[i].z - center.z) * (position[i].z - center.z);
      double distance = sqrt(distance2);
      if (distance < LASER_DIAMETER * 0.5 + EPS) {
        heatFlux[i] = Q;
      }
    }
    

    /*
    if ( x_MAX*0.5 - PARTICLE_DISTANCE < position[i].x && position[i].x < x_MAX*0.5 + PARTICLE_DISTANCE) {
      heatFlux[i] = Q;
    }
    */  
  }
}
