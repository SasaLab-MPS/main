/*=====================================================================
  calCurvature.cpp   
  Yota INOUE (2021) 
  表面張力の曲率
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double calCurvature(int particleNumber) {
  double distance, distance2;
  double w;
  double xij, yij, zij;
  double n_dash;
  int i = particleNumber;

  searchBucket(i);
  int j;
  n_dash = 0.0;
  for (int k = 0; k < (int)neghPar.size(); k++)
  {
    j = neghPar[k]; // particle jの番号
    if ((j == i) || (position[j].particleType == GHOST))
      continue; // その粒子自身とゴースト粒子は計算に含めない
    // 粒子間距離の計算
    xij = position[j].x - position[i].x;
    yij = position[j].y - position[i].y;
    zij = position[j].z - position[i].z;
    distance2 = (xij * xij) + (yij * yij) + (zij * zij);
    distance = sqrt(distance2);
    // 影響範囲か？
    if (distance < Re_forLaplacian)
    {
      w = weightForSUrfacetension(distance, Re_forLaplacian); // 重み関数
      // 法線ベクトルの計算
      n_dash += w;
    }
  }

  double theta;
  double kappa;

  theta = 0.5 * M_PI * n_dash / N0_forSurfaceTension;
  kappa = 2 * cos(theta) / RADIUS_FOR_LAPLACIAN;

  return kappa;
}