/*=====================================================================
  removeNegativeTemperature.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  0 Pa未満の圧力が発生した場合0 Paに修正
  Last update: Feb 23, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void removeNegativeTemperature(void) {
    int i;

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (temperature(i) < INITIAL_TEMPERATURE)
            temperature(i) = INITIAL_TEMPERATURE;
    }
}