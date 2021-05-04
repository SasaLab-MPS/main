/*=====================================================================
  checkTemperature.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱分布を計算
  Last update: Mar 30 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void checkTemperature(void) {
    for(int i = 0; i < NumberOfParticles; i++) {
        if (position[i].particleType == WALL || position[i].particleType == DUMMY_WALL || position[i].particleType == GHOST) {
            temperature(i) = INITIAL_TEMPERATURE;
        }
    }
}