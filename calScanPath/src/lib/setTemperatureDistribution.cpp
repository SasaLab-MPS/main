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
  double rho, c;
  double enthalpy;            // エンタルピー，熱含量 (J)

  rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
  c = SPECIFIC_HEAT_CAPACITY; // 比熱容量

  // 温度分布の計算
  for(int i = 0; i < NP; i++) {
    enthalpy = calLaserIntensity(position[i]);
    // 温度の計算(溶融・蒸発は考えない 2021.6.11)
    temperature[i] = enthalpy / (rho*c);

    // 溶融・蒸発を考える場合 2021.6.14
    /*
    double melt = enthalpy * rho * c * MELTING_TEMPERATURE;
    double vapor = melt + rho * LATENT_HEAT;
    if (enthalpy < MELTING_TEMPERATURE)
    {
      // 個体のまま
      position[i].particleType = SOLID;
    }
    else if (melt <= enthalpy < melt + vapor)
    {
      // 溶融
      position[i].particleType = FLUID;
    }
    else
    {
      // 蒸発
      position[i].particleType = GAS;
    } 
    */   
  }
}
