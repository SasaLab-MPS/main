/*=====================================================================
  exceptionalProcessingForBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  例外処理
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void exceptionalProcessingForBoundaryCondition(void)
{
    /* If tere is no Dirichlet boundary condition on the fluid, 
     increase the diagonal terms of the matrix for an exception. This allows us to solve the matrix without Dirichlet boundary conditions. */
    checkBoundaryCondition();
    increaseDiagonalTerm();
}
