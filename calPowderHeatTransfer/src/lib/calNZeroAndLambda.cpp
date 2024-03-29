/*=====================================================================
  calNZeroAndLambda.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粒子の位置と速度の初期化する関数
  Last update: Feb 20, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void calNZeroAndLambda(void) {
    int iX, iY, iZ;
    int iZ_start, iZ_end;
    double xj, yj, zj, distance, distance2;
    double xi, yi, zi;

    // 次元の判定
    if (DIM == 2) {
        iZ_start = 0;
        iZ_end = 1;
    } else {
        iZ_start = -4;
        iZ_end = 5;
    }

    // 初期化，エヌゼロ
    N0_forNumberDensity = 0.0; // 粒子数密度の初期化
    N0_forGradient = 0.0;
    N0_forLaplacian = 0.0;
    Lambda = 0.0;
    xi = 0.0;
    yi = 0.0;
    zi = 0.0;

    // 自分を中心に周りの粒子との密度を計算
    for (iX = -4; iX < 5; iX++) {
        for (iY = -4; iY < 5; iY++) {
            for (iZ = iZ_start; iZ < iZ_end; iZ++) {
                if (((iX == 0) && (iY == 0)) && (iZ == 0))
                    continue;
                //　粒子間距離の計算
                xj = PARTICLE_DISTANCE * (double)(iX);
                yj = PARTICLE_DISTANCE * (double)(iY);
                zj = PARTICLE_DISTANCE * (double)(iZ);
                distance2 = (xj - xi) * (xj - xi) + (yj - yi) * (yj - yi) + (zj - zi) * (zj - zi);
                distance = sqrt(distance2);

                // 影響半径を用いた重み関数の計算
                N0_forNumberDensity += weight(distance, Re_forNumberDensity); // 初期粒子密度の計算
                N0_forGradient += weight(distance, Re_forGradient);
                N0_forLaplacian += weight(distance, Re_forLaplacian);
                N0_forSurfaceTension += (distance < Re_forLaplacian) ? 1 : 0; // 曲率計算用の密度
                Lambda += distance2 * weight(distance, Re_forLaplacian);
            }
        }
    }
    Lambda = Lambda / N0_forLaplacian;
}