/*=====================================================================
  setBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  ポアソン方程式のディリクレ境界条件を設定(圧力の固定をするかしないかを設定)
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void setBoundaryCondition(void)
{
    int i;
    double n0 = N0_forNumberDensity;
    double beta = THRESHOLD_RATIO_OF_NUMBER_DENSITY;

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (ParticleType[i] == GHOST || ParticleType[i] == DUMMY_WALL)
        {
            BoundaryCondition[i] = GHOST_OR_DUMMY;      // 計算に関与しない
        }
        else if (NumberDensity[i] < beta * n0)      
        {
            BoundaryCondition[i] = SURFACE_PARTICLE;     // 自由表面上の粒子の場合
        }
        else
        {
            BoundaryCondition[i] = INNER_PARTICLE;       // 内部粒子
        }
    }
}
