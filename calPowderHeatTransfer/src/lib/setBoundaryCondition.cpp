/*=====================================================================
  setBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  ポアソン方程式のディリクレ境界条件を設定(圧力の固定をするかしないかを設定)
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void setBoundaryCondition(void)
{
    double n0 = N0_forNumberDensity;
    double beta = THRESHOLD_RATIO_OF_NUMBER_DENSITY;
    boundaryCondition.resize(NumberOfParticles);

    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (particle[i].particleType == GHOST || particle[i].particleType == DUMMY_WALL)
        {
            boundaryCondition[i] = GHOST_OR_DUMMY;  // 計算に関与しない
        }
        else if (numberDensity[i] < beta * n0)      // 自由表面上の粒子の場合
        {
            boundaryCondition[i] = SURFACE_PARTICLE;
        }
        else
        {
            boundaryCondition[i] = INNER_PARTICLE;  // 内部粒子または壁粒子
        }
    }
}