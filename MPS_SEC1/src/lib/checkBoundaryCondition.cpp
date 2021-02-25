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

    calBkt();
    cout << "bkt size:" << bkt.size() << endl; 
    cout << "bkt[1][0]:" << bkt[1][0] << endl;

    do
    {
        count = 0;
        for (int i = 0; i < NumberOfParticles; i++)
        {
            if (flagForCheckingBoundaryCondition[i] == DIRICHLET_BOUNDARY_IS_CONNECTED)
            {
                /* バケット法による粒子の探索 */
                searchBkt(i);
                //cout << "neghPar:" << neghPar[2] << endl; // 反応せず:戻り値をvectorにするべきか？
                int j;
                for(int k = 0; k < neghPar.size(); k++) {
                    j = neghPar[k];     // particle j
                    if (j == i)
                        continue; 
                    // その粒子自身とゴースト粒子は計算に含めない
                    if ((position[j].particleType == GHOST) || (position[j].particleType == DUMMY_WALL))
                        continue;
                    if (flagForCheckingBoundaryCondition[j] == DIRICHLET_BOUNDARY_IS_NOT_CONNECTED)
                    {
                        xij = position[j].x - position[i].x;
                        yij = position[j].y - position[i].y;
                        zij = position[j].z - position[i].z;
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