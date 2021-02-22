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

    // NxNの正方行列を設定，N:粒子数
    for (i = 0; i < NumberOfParticles; i++)
    {
        if (boundaryCondition[i] != INNER_PARTICLE)
            continue;

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
                        if ((par_j == i) || (position[par_j].particleType == GHOST))
                            continue; // その粒子自身とゴースト粒子は計算に含めない
                        // 粒子間距離の計算
                        xij = position[par_j].x - position[i].x;
                        yij = position[par_j].y - position[i].y;
                        zij = position[par_j].z - position[i].z;
                        distance2 = (xij * xij) + (yij * yij) + (zij * zij);
                        distance = sqrt(distance2);
                        // 影響範囲内か？
                        if (distance2 < collisionDistance2)
                        {
                            if (distance >= Re_forLaplacian)
                                continue;
                            coefficientIJ = a * weight(distance, Re_forLaplacian) / FluidDensity;
                            // 係数行列の中身aijを計算
                            coefficientMatrix(i, j) = (-1.0) * coefficientIJ;
                            coefficientMatrix(i, i) += coefficientIJ;
                        }
                    }
                }
            }
        }
        coefficientMatrix(i, i) += (COMPRESSIBILITY) / (DT * DT);
    }
    exceptionalProcessingForBoundaryCondition(); // ディリクレ境界条件を満たさない粒子の例外処理
}