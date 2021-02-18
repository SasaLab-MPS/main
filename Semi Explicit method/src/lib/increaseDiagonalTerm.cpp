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
    for (int i = 0; i < NumberOfParticles; i++)
    {
        // 自由表面を持たない粒子同士の接近が発生した場合に備えた例外処理，計算を収束させるため
        if (FlagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            A(i, i) = 2.0*A(i, i);
        }
    }
}
