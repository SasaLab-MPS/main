/*=====================================================================
  setMatrixByList.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力に関する連立一次方程式の係数行列を設定
  リストを用いて近傍粒子の捜索を高速化
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void setMatrixByList (void)
{
    double xij, yij, zij;
    double distance, distance2;
    double coefficientIJ;
    double n0 = N0_forLaplacian;
    int i, j;
    double a;

    a = 2.0 * DIM / (n0 * Lambda);

    // NxNの正方行列を設定，N:粒子数
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (BoundaryCondition[i] != INNER_PARTICLE)
            continue;
        
        // 粒子の所属するバケットのid
        int bktid[3];    // 0:x, 1:y, 2:z
        for(int j = 0; j < 3; j++) {
            bktid[j] = (int)((Position[i*3+j] - Pos_MIN[j]) * DBinv) + 1;
        }

        // 対象のバケット周辺の粒子のみを探索
        for(int jz = bktid[2]-1; jz <= bktid[2]+1; jz++) {
            for (int jy = bktid[1]-1; jy <= bktid[2]+1; jy++) {
                for (int jx = bktid[0] - 1; jx <= bktid[0]+1; jx++) {
                    int id = jz * nBxy + jy * nBx + jx;
                    if (bkt[id][0] == -1)   // バケット内に粒子が存在しない
                    {
                        continue;
                    }
                    // バケット内の粒子と対象の粒子との相互作用を計算
                    for(int j = 0; j < bkt[id].size(); j++) {
                        int paj = bkt[id][j];   // particle j
                        if ((paj == i) || (BoundaryCondition[paj] == GHOST_OR_DUMMY))
                        {
                            continue;
                        }
                        // 粒子iとjの距離
                        xij = Position[paj * 3] - Position[i * 3];
                        yij = Position[paj * 3 + 1] - Position[i * 3 + 1];
                        zij = Position[paj * 3 + 2] - Position[i * 3 + 2];
                        distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                        distance = sqrt(distance2);
                        // 影響範囲内か?
                        if (distance >= Re_forLaplacian)
                            continue;
                        coefficientIJ = a * weight(distance, Re_forLaplacian) / FluidDensity;
                        // 係数行列の中身aijを計算
                        A(i, j) = (-1.0) * coefficientIJ;
                        A(i, i) += coefficientIJ;
                    }
                }
            }
        }
        A(i, i) += (COMPRESSIBILITY) / (DT * DT);
    }
    exceptionalProcessingForBoundaryCondition(); // ディリクレ境界条件を満たさない粒子の例外処理
}