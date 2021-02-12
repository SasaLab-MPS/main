/*=====================================================================
  setMatrix.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式の係数行列を設定
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void setMatrix(void)
{
    double xij, yij, zij;
    double distance, distance2;
    double coefficientIJ;
    double n0 = N0_forLaplacian;
    int i, j;
    double a;
    int n = NumberOfParticles;

    for (i = 0; i < NumberOfParticles; i++)
    {
        for (j = 0; j < NumberOfParticles; j++)
        {
            CoefficientMatrix[i * n + j] = 0.0;
        }
    }

    a = 2.0 * DIM / (n0 * Lambda);
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (BoundaryCondition[i] != INNER_PARTICLE)
            continue;
        for (j = 0; j < NumberOfParticles; j++)
        {
            if ((j == i) || (BoundaryCondition[j] == GHOST_OR_DUMMY))
                continue;
            xij = Position[j * 3] - Position[i * 3];
            yij = Position[j * 3 + 1] - Position[i * 3 + 1];
            zij = Position[j * 3 + 2] - Position[i * 3 + 2];
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            if (distance >= Re_forLaplacian)
                continue;
            coefficientIJ = a * weight(distance, Re_forLaplacian) / FluidDensity;
            CoefficientMatrix[i * n + j] = (-1.0) * coefficientIJ;      // 係数行列の中身aijを計算
            CoefficientMatrix[i * n + i] += coefficientIJ;
        }
        CoefficientMatrix[i * n + i] += (COMPRESSIBILITY) / (DT * DT);  // 流体の圧縮率に関する計算
    }
    exceptionalProcessingForBoundaryCondition();        // ディリクレ境界条件を満たさない粒子の例外処理
}
