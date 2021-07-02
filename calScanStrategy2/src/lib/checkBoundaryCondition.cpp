/*=====================================================================
  checkBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  境界条件のチェック
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void checkBoundaryCondition(void)
{
    int count;
    double xij, yij, zij, distance2;
    flagForCheckingBoundaryCondition.resize(NumberOfParticles);

    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (boundaryCondition[i] == GHOST_OR_DUMMY) // setBoundaryConditionで設定
        {
            flagForCheckingBoundaryCondition[i] = GHOST_OR_DUMMY;
        }
        else if (boundaryCondition[i] == SURFACE_PARTICLE)
        {
            flagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_CONNECTED;
        }
        else
        {
            flagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_NOT_CONNECTED;
        }
    }

    // 境界条件は全ての粒子に対して計算しなければならない．バケット法を使えない
    do
    {
        count = 0;
        for (int i = 0; i < NumberOfParticles; i++)
        {
            if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_CONNECTED)
            {
                for (int j = 0; j < NumberOfParticles; j++)
                {
                    if (j == i)
                        continue;
                    if ((particle[j].particleType == GHOST) || (particle[j].particleType == DUMMY_WALL))
                        continue;
                    if (flagForCheckingBoundaryCondition[j] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
                    {
                        xij = particle[j].x - particle[i].x;
                        yij = particle[j].y - particle[i].y;
                        zij = particle[j].z - particle[i].z;
                        distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                        if (distance2 >= Re2_forLaplacian)
                            continue;
                        flagForCheckingBoundaryCondition[j] = DIRICHLET_BOUNDARY_IS_CONNECTED;
                    }
                }
                flagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_CHECKED;
                count++;
            }
        }
    } while (count != 0); /* This procedure is repeated until the all fluid or wall particles (which have Dirhchlet boundary condition in the particle group) are in the state of "DIRICHLET_BOUNDARY_IS_CHECKED".*/


    for (int i = 0; i < NumberOfParticles; i++)
    {
        if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            fprintf(stderr, "WARNING: There is no dirichlet boundary condition for %d_th particle.\n", i);
        }
    }
}