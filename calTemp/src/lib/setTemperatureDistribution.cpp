/*=====================================================================
  setTemperatureDistribution.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  初期温度分布を与える
  Last update: Mar 15, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setTemperatureDistribution(void)
{
  int NP = NumberOfParticles;
 
  if (Time < 0.002) {
    for (int i = 0; i < NP; i++)
    {
      temperature(i) = INITIAL_TEMPERATURE;
      if (position[i].x < 0.5 * x_MAX)
      {
        temperature(i) = 500;
        //enthalpy[i] = LASER_POWER;
      }
      if (position[i].particleType == WALL || position[i].particleType == DUMMY_WALL || position[i].particleType == GHOST)
      {
        temperature[i] = INITIAL_TEMPERATURE;
      }
    }
  }
  
  /*
  if (Time < 0.002)
  {
    for(int i = 0; i < NumberOfParticles; i++) {
      heatFlux[i] = 0.0;
      if (y_MAX * 0.5 - EPS < position[i].x && position[i].x < y_MAX * 0.5 + EPS)
      {
        heatFlux[i] = LASER_POWER * PARTICLE_DISTANCE * PARTICLE_DISTANCE;
      }      
    }  
  } else {
    for (int i = 0; i < NumberOfParticles; i++)
    {
      heatFlux[i] = 0.0;
    }
  }
  */
  
  
  /*
  double area = M_PI * 0.25 * (LASER_DIAMETER * LASER_DIAMETER);
  double piece = area / (M_PI * 0.25 * (PARTICLE_DISTANCE * PARTICLE_DISTANCE));
  double q = (LASER_POWER) / piece;   // W/m^2
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
        heatFlux[i] = q;
      }
    }
    else
    {
      double distance2 = (position[i].x - center.x) * (position[i].x - center.x) + (position[i].y - center.y) * (position[i].y - center.y) + (position[i].z - center.z) * (position[i].z - center.z);
      double distance = sqrt(distance2);
      if (distance < LASER_DIAMETER * 0.5 + EPS) {
        heatFlux[i] = q;
      }
    }  
  }
  */
}
