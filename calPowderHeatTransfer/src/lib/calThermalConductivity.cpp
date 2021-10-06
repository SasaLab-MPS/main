/*=====================================================================
  calThermalConductivityAndHeatTransfer.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  個体の熱伝導率・粉末の熱伝導率を設定
  Last update: Oct. 4, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void calThermalConductivity(int i) {
  
  if (particle[i].particleType == POWDER)
  {
    if (temperature[i] < MELTING_TEMPERATURE)
    {
      // 融点未満
      double kp = calPowderHeatTransfer(temperature[i]);
      ThermalConductivity[i] = kp;
    } else {
      // 溶融後
      particle[i].particleType = SOLID;
      ThermalConductivity[i] = HEAT_CONDUCTIVITY;
    }   
  } 
  else 
  {
    ThermalConductivity[i] = HEAT_CONDUCTIVITY;
  }

}