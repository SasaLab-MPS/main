/*=====================================================================
  laserRadiation.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  レーザ照射中の各値を計算
  Last update: June 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void laserRadiation(void) {
    string strategy = "Island";
    calScanPath(strategy, SCAN_VECTOR_LENGTH);   // 走査パターンの計算
}