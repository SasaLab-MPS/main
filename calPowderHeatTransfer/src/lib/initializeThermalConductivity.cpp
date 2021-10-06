/*=====================================================================
  initializeThermalConductivity.cpp   
  Yota INOUE (2021) 
  熱伝導率の計算
  Last update: Oct. 4, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void initializeThermalConductivity(void) {
    int NP = NumberOfParticles;
    double kp;

    for (int i = 0; i < NP; i++)
    {
        ThermalConductivity[i] = HEAT_CONDUCTIVITY;

        if (particle[i].particleType == POWDER)
        {
            kp = calPowderHeatTransfer(temperature[i]);
            ThermalConductivity[i] = kp;
        }  
    }
    
}