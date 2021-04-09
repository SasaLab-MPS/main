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
  double area = PARTICLE_DISTANCE*PARTICLE_DISTANCE;
  double Q = HEAT_INPUT * area * 10e6;

  for(int i = 0; i < NumberOfParticles; i++) {
    heatFlux[i] = 0.0;
    if ( x_MAX*0.5 - PARTICLE_DISTANCE < position[i].x && position[i].x < x_MAX*0.5 + PARTICLE_DISTANCE) {
      heatFlux[i] = Q;
    }  
  }
}
