/*=====================================================================
  checkBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  境界条件のチェック
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void checkBoundaryCondition(void)
{
    int i, j, count;
    double xij, yij, zij, distance2;

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (BoundaryCondition[i] == GHOST_OR_DUMMY)
        {
            FlagForCheckingBoundaryCondition[i] = GHOST_OR_DUMMY;
        }
        else if (BoundaryCondition[i] == SURFACE_PARTICLE)
        {
            FlagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_CONNECTED;
        }
        else
        {
            FlagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_NOT_CONNECTED;
        }
    }

    do
    {
        count = 0;
        for (i = 0; i < NumberOfParticles; i++)
        {
            if (FlagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_CONNECTED)
            {
                for (j = 0; j < NumberOfParticles; j++)
                {
                    if (j == i)
                        continue;
                    if ((ParticleType[j] == GHOST) || (ParticleType[j] == DUMMY_WALL))
                        continue;
                    if (FlagForCheckingBoundaryCondition[j] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
                    {
                        xij = Position[j * 3] - Position[i * 3];
                        yij = Position[j * 3 + 1] - Position[i * 3 + 1];
                        zij = Position[j * 3 + 2] - Position[i * 3 + 2];
                        distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                        if (distance2 >= Re2_forLaplacian)
                            continue;
                        FlagForCheckingBoundaryCondition[j] = DIRICHLET_BOUNDARY_IS_CONNECTED;
                    }
                }
                FlagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_CHECKED;
                count++;
            }
        }
    } while (count != 0); /* This procedure is repeated until the all fluid or wall particles (which have Dirhchlet boundary condition in the particle group) are in the state of "DIRICHLET_BOUNDARY_IS_CHECKED".*/

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (FlagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            fprintf(stderr, "WARNING: There is no dirichlet boundary condition for %d-th particle.\n", i);
        }
    }
}
