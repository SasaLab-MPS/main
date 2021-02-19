/*=====================================================================
  setMatrix.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式の係数行列を設定
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setMatrix(void)
{
    double xij, yij, zij;
    double distance, distance2;
    double coefficientIJ;
    double n0 = N0_forLaplacian;
    int i, j;
    double a;

    a = 2.0 * DIM / (n0 * Lambda);

    cout << "call setMatrix" << endl;
    // NxNの正方行列を設定，N:粒子数
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
            // 係数行列の中身aijを計算
            A(i, j) = (-1.0) * coefficientIJ;
            A(i, i) += coefficientIJ;
        }
        A(i, i) += (COMPRESSIBILITY) / (DT * DT);
    }
    exceptionalProcessingForBoundaryCondition();        // ディリクレ境界条件を満たさない粒子の例外処理
}
