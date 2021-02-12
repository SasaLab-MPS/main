/*=====================================================================
  calPressure.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  圧力を計算(陰解法)
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void calPressure(void)
{
    calNumberDensity();         // 粒子数密度を計算
    setBoundaryCondition();     // 境界条件の設定(ディリクレ条件)
    setSourceTerm();            // ポアソン方程式の右辺ベクトルの設定
    setMatrix();                // 係数行列Aの設定
    solveSimultaniousEquationsByGaussEliminationMethod();   // 掃き出し方による解の決定(N^3のため計算コストが重い)
    removeNegativePressure();   // 圧力が0未満になった場合を0処理
    setMinimumPressure();       // 各粒子近傍の最低圧力を計算(圧力勾配の計算に使用)
}