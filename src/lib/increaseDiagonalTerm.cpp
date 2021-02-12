/*=====================================================================
  increaseDiagonalTerm.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式の係数行列を設定
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void increaseDiagonalTerm(void)
{
    int i;
    int n = NumberOfParticles;

    for (i = 0; i < n; i++)
    {
        if (FlagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            CoefficientMatrix[i * n + i] = 2.0 * CoefficientMatrix[i * n + i];
        }
    }
}
