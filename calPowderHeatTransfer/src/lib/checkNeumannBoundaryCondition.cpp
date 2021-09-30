/*=====================================================================
  setNeumannBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱伝導方程式にノイマン境界条件を設定
  Last update: June 15, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void checkNeumannBoundaryCondition(void)
{
    double n0 = N0_forNumberDensity;
    double beta = THRESHOLD_RATIO_OF_NUMBER_DENSITY;
    NeumannBoundaryCondition.resize(NumberOfParticles);

    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (particle[i].particleType == GHOST || particle[i].particleType == DUMMY_WALL)
        {
            NeumannBoundaryCondition[i] = GHOST_OR_DUMMY; // 計算に関与しない
        }
        else if (numberDensity[i] < beta * n0) // 自由表面上の粒子の場合
        {
            NeumannBoundaryCondition[i] = SURFACE_PARTICLE;
        }
        else
        {
            NeumannBoundaryCondition[i] = INNER_PARTICLE; // 内部粒子または壁粒子
        }
    }
}