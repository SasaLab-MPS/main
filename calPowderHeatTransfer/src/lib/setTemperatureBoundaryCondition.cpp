/*=====================================================================
  setTemperatureBoundaryCondition.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  温度の境界条件を設定(ノイマン条件を設定)
  Last update: Mar 30 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void setTemperatureBoundaryCondition(void)
{    
    checkNeumannBoundaryCondition();    // ノイマン境界条件の設定

    // ノイマン境界条件に基づいた熱の流入・流出の設定
    double rho, c, lmb, k;
    int NP = NumberOfParticles;

    rho = SOLID_DENSITY;        // 相変化を考慮するなら変更する
    c = SPECIFIC_HEAT_CAPACITY; // 比熱容量

    // 表面からの放熱を計算
    if (DIM == 2) {
        for (int i = 0; i < NP; i++) {
            if (NeumannBoundaryCondition[i] == SURFACE_PARTICLE) {
                if (particle[i].z == Pos_MIN[2]) {
                    // ベースプレート直上の場合
                    lmb = HEAT_CONDUCTIVITY; // 熱伝導率
                } else {
                    // 粉末に接している表面の場合
                    lmb = calPowderHeatTransfer(temperature[i]);
                }

                double dT = INITIAL_TEMPERATURE - temperature[i];
                double dx = PARTICLE_DISTANCE;
                double alpha = k * (dT / dx) * DT;
                temperature[i] += alpha;    // 境界条件は係数行列ではなく，右辺に追加される
            }
        }
    } else {
        for (int i = 0; i < NP; i++) {
            // 最上層からの放熱は無視 
            if (particle[i].z == z_MAX) { continue; }
            
            if (NeumannBoundaryCondition[i] == SURFACE_PARTICLE) {
                if (particle[i].z == Pos_MIN[2]) {
                    // ベースプレート直上の場合
                    lmb = HEAT_CONDUCTIVITY; // 熱伝導率
                } else {
                    // 粉末に接している表面の場合
                    lmb = calPowderHeatTransfer(temperature[i]);
                }

                k = lmb / (rho * c);
                double dT = INITIAL_TEMPERATURE - temperature[i];
                double dx = PARTICLE_DISTANCE;
                double alpha = k * (dT / dx) * DT;
                temperature[i] += alpha;    // 境界条件は係数行列ではなく，右辺に追加される
            }         
        }
    }
         
}