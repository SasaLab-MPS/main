/*=====================================================================
  setSourceTerm.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式のソースタームを設定
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setSourceTerm(void)
{
    double n0 = N0_forNumberDensity;
    double gamma = RELAXATION_COEFFICIENT_FOR_PRESSURE; // 計算を安定させるための緩和係数(0.2としている)

    for (int i = 0; i < NumberOfParticles; i++)
    {
        sourceTerm(i) = 0.0;
        if (particle[i].particleType == GHOST || particle[i].particleType == DUMMY_WALL)
            continue;
        if (boundaryCondition[i] == INNER_PARTICLE)
        {
            sourceTerm(i) = gamma * (1.0 / (DT * DT)) * ((numberDensity[i] - n0) / n0);
        }
        else if (boundaryCondition[i] == SURFACE_PARTICLE)
        {
            sourceTerm(i) = 0.0;
        }
    }
}