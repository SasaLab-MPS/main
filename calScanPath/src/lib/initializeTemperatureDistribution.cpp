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

    for (int i = 0; i < NP; i++) {
        temperature(i) = INITIAL_TEMPERATURE;
    }
}