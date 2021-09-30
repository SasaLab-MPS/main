/*=====================================================================
  calTemperature.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱分布を計算
  Last update: Mar 30 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void calTemperature(void) {
  setTemperatureDistribution();       // 初期温度分布を与える
  calTemperatureLaplacian();          // ラプラシアンモデルに基づいて温度場を計算(方程式右辺の設定, 係数行列の設定)
  setTemperatureBoundaryCondition();  // 境界条件の設定 = 温度のチェック
  solveTemperatureByCGmethod();       // 共役勾配法による高速解法
  removeNegativeTemperature();        // 温度が最低温度未満になった場合を0処理
}