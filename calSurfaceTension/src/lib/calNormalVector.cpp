/*=====================================================================
  calNormalVector.cpp   
  Yota INOUE (2021) 
  法線ベクトルの計算
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calNormalVector(int particleNumber) {
    double distance, distance2;
    double w;
    double xij, yij, zij;
    double a;
    double normal_x, normal_y, normal_z;

    a = DIM / N0_forLaplacian;  // 係数
    calBucket();                // 粒子が所属するバケットを計算

    int i = particleNumber;
    if (position[i].particleType != FLUID) {
        return;     // 流体でなければ計算終了
    }

    normal_x = 0.0;
    normal_y = 0.0;
    normal_z = 0.0;

    searchBucket(i);
    int j;
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
        if (distance < Re_forLaplacian) {
            w = weight(distance, Re_forLaplacian); // 重み関数
            
            normal_x += (numberDensity[j] - N0_forNumberDensity) * xij * w / distance2;
            normal_y += (numberDensity[j] - N0_forNumberDensity) * yij * w / distance2;
            normal_z += (numberDensity[j] - N0_forNumberDensity) * zij * w / distance2;
        }
    }

    // 法線ベクトルの更新
    normal_x *= a;
    normal_y *= a;
    normal_z *= a;
    // ノルムの計算
    double norm;
    norm = sqrt( (normal_x * normal_x) + (normal_y * normal_y) + (normal_z * normal_z) );
    // 法線ベクトルの単位ベクトル化
    normalVector[i].x = normal_x / norm;
    normalVector[i].y = normal_y / norm;
    normalVector[i].z = normal_z / norm;

}