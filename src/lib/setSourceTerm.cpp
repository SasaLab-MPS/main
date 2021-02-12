/*=====================================================================
  setSourceTerm.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式のソースタームを設定
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void setSourceTerm(void)
{
    int i;
    double n0 = N0_forNumberDensity;
    double gamma = RELAXATION_COEFFICIENT_FOR_PRESSURE;     // 計算を安定させるための緩和係数(0.2としている)

    for (i = 0; i < NumberOfParticles; i++)
    {
        SourceTerm[i] = 0.0;
        if (ParticleType[i] == GHOST || ParticleType[i] == DUMMY_WALL)
            continue;
        if (BoundaryCondition[i] == INNER_PARTICLE)
        {
            SourceTerm[i] = gamma * (1.0 / (DT * DT)) * ((NumberDensity[i] - n0) / n0);
        }
        else if (BoundaryCondition[i] == SURFACE_PARTICLE)
        {
            SourceTerm[i] = 0.0;
        }
    }
}
