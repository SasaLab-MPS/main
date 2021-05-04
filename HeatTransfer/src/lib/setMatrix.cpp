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
    double coefficientIJ, coefficientMatrixII;
    double n0 = N0_forLaplacian;
    double a;

    P_aij.clear(); // 係数行列の初期化

    a = 2.0 * DIM / (n0 * Lambda);

    // NxNの正方行列を設定，N:粒子数
    for (int i = 0; i < NumberOfParticles; i++) {
        coefficientMatrixII = 0.0;
        if (boundaryCondition[i] != INNER_PARTICLE) continue;
        /* バケット法による粒子の探索効率向上 */
        searchBucket(i);
        // 粒子の所属するバケットのid
        int j;
        for(int k = 0; k < (int)neghPar.size(); k++) {
            j = neghPar[k];
            if ((j == i) || (boundaryCondition[j] == GHOST_OR_DUMMY))
                continue; // その粒子自身とゴースト粒子は計算に含めない
            // 粒子間距離の計算
            xij = position[j].x - position[i].x;
            yij = position[j].y - position[i].y;
            zij = position[j].z - position[i].z;
            distance2 = (xij * xij) + (yij * yij) + (zij * zij);
            distance = sqrt(distance2);
            // 影響範囲内か？
            if (distance >= Re_forLaplacian)
                continue;
            coefficientIJ = a * weight(distance, Re_forLaplacian) / FluidDensity;
            // 係数行列の中身を計算
            P_aij.push_back(Tri(i, j, (-1.0) * coefficientIJ));
            coefficientMatrixII += coefficientIJ;
        }
        coefficientMatrixII += (COMPRESSIBILITY) / (DT * DT);
        P_aij.push_back(Tri(i, i, coefficientMatrixII));
    }
    // 係数行列の設定
    coefficientMatrix.setFromTriplets(P_aij.begin(), P_aij.end());
    // 例外処理
    exceptionalProcessingForBoundaryCondition(); // ディリクレ境界条件を満たさない粒子の例外処理
}