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
  double volume, mass;

  rho = SOLID_DENSITY;               // 相変化を考慮するなら変更する
  c = SPECIFIC_HEAT_CAPACITY * 1e-3; // 比熱容量，Jに換算
  volume = pow(PARTICLE_DISTANCE, 3);
  mass = rho * volume;

  // 温度分布の計算，レーザ吸収率を乗じるべき・ノイマン境界条件を設定した方が良い
  for(int i = 0; i < NP; i++) {
    enthalpy = calLaserIntensity(particle[i]);
    // 温度の計算(溶融・蒸発は考えない 2021.6.11)
    temperature[i] += LASER_ABSORPTION_RATE * enthalpy / (mass * c);

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
