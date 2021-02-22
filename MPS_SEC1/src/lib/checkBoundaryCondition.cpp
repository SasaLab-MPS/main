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
    int i, j, count;
    double xij, yij, zij, distance2;
    flagForCheckingBoundaryCondition.resize(NumberOfParticles);

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (boundaryCondition[i] == GHOST_OR_DUMMY)
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

    do
    {
        count = 0;
        for (i = 0; i < NumberOfParticles; i++)
        {
            if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_CONNECTED)
            {
                /* バケット法による粒子の探索効率向上 */
                // 粒子の所属するバケットのid
                int bktid[3]; // 0:x, 1:y, 2:z
                bktid[0] = (int)((position[i].x - Pos_MIN[0]) * DBinv) + 1;
                bktid[1] = (int)((position[i].y - Pos_MIN[1]) * DBinv) + 1;
                bktid[2] = (int)((position[i].z - Pos_MIN[2]) * DBinv) + 1;

                // 対象のバケット周辺の粒子のみを探索 3*3*3=27
                for (int jz = bktid[2] - 1; jz <= bktid[2] + 1; jz++) {
                    for (int jy = bktid[1] - 1; jy <= bktid[1] + 1; jy++) {
                        for (int jx = bktid[0] - 1; jx <= bktid[0] + 1; jx++) {
                            // バケットのidを計算, 2次元のときnBxy = 0としている
                            int id = jz * nBxy + jy * nBx + jx;
                            if (bkt[id][0] == -1) // バケット内に粒子が存在しない
                            {
                                continue;
                            }
                            // バケット内の粒子と対象の粒子との粘性相互作用を計算
                            for (int j = 0; j < bkt[id].size(); j++)
                            {
                                int par_j = bkt[id][j]; // particle j
                                if (par_j == i)
                                    continue; // その粒子自身とゴースト粒子は計算に含めない
                                if ((position[par_j].particleType == GHOST) || (position[par_j].particleType == DUMMY_WALL))
                                    continue;
                                if (flagForCheckingBoundaryCondition[par_j] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
                                {
                                    xij = position[par_j].x - position[i].x;
                                    yij = position[par_j].y - position[i].y;
                                    zij = position[par_j].z - position[i].z;
                                    distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                                    if (distance2 >= Re2_forLaplacian)
                                        continue;
                                    flagForCheckingBoundaryCondition[par_j] = DIRICHLET_BOUNDARY_IS_CONNECTED;
                                }
                            }
                        }
                    }
                }
                flagForCheckingBoundaryCondition[i] = DIRICHLET_BOUNDARY_IS_CHECKED;
                count++;
            }
        }
    } while (count != 0); /* This procedure is repeated until the all fluid or wall particles (which have Dirhchlet boundary condition in the particle group) are in the state of "DIRICHLET_BOUNDARY_IS_CHECKED".*/

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
        {
            fprintf(stderr, "WARNING: There is no dirichlet boundary condition for %d-th particle.\n", i);
        }
    }
}