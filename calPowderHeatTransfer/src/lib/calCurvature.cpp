/*=====================================================================
  calCurvature.cpp   
  Yota INOUE (2021) 
  表面張力の曲率
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

double calCurvature(int particleNumber) {
  double distance, distance2;
  double xij, yij, zij;
  double n_dash;
  int i = particleNumber;

  searchBucket(i);
  int j;
  n_dash = 0.0;
  for (int k = 0; k < (int)neghPar.size(); k++)
  {
    j = neghPar[k]; // particle jの番号
    if ((j == i) || (particle[j].particleType == GHOST))
      continue; // その粒子自身とゴースト粒子は計算に含めない
    // 粒子間距離の計算
    xij = particle[j].x - particle[i].x;
    yij = particle[j].y - particle[i].y;
    zij = particle[j].z - particle[i].z;
    distance2 = (xij * xij) + (yij * yij) + (zij * zij);
    distance = sqrt(distance2);
    // 影響範囲か?
    if (distance < Re_forLaplacian)
    {
      // 密度の計算
      n_dash += 1;
    }
  }

  double theta; // 角度
  double kappa; // 曲率

  theta = 0.5 * M_PI * n_dash / N0_forSurfaceTension;
  kappa = 2 * cos(theta) / RADIUS_FOR_LAPLACIAN;

  return kappa;
}