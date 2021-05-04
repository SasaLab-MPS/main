/*=====================================================================
  increaseDiagonalTerm.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式の係数行列を設定
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void increaseDiagonalTerm(void)
{
    int n = NumberOfParticles;

    for (int i = 0; i < n; i++)
    {
        if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            coefficientMatrix(i, i) = 2.0 * coefficientMatrix(i, i);
        }
    }
}
