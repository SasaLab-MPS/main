/*=====================================================================
  initializeTemperatureDistribution.cpp   
  Yota INOUE (2021) 
  温度分布の初期化
  Last update: Mar 30, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void initializeTemperatureDistribution(void) {
    int NP = NumberOfParticles;
    double mass, area, heatFlux;

    area = PARTICLE_DISTANCE *PARTICLE_DISTANCE;
    mass = area * PARTICLE_DISTANCE * SOLID_DENSITY;
    heatFlux = area * HEAT_INPUT;

    for (int i = 0; i < NP; i++) {
        temperature(i) = INITIAL_TEMPERATURE;
        /*
        if (0.5 * x_MAX - EPS < position[i].x && position[i].x < 0.5 * x_MAX + EPS)
        {
            temperature(i) = heatFlux / (mass * SPECIFIC_HEAT_CAPACITY);
            //enthalpy[i] = LASER_POWER;
        }
        if (position[i].particleType == WALL || position[i].particleType == DUMMY_WALL || position[i].particleType == GHOST)
        {
            temperature(i) = INITIAL_TEMPERATURE;
        }
        */
    }
}