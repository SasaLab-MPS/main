/*=====================================================================
  calScangPath.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calScanPath(int strategy)
{
    switch (strategy)
    {
    case SINGLE:     // シングルスキャン
        centerOfLaser.x = Time * SCAN_SPEED;
        centerOfLaser.y = 0.5 * y_MAX;
        break;

    case ISLAND:    // アイランドスキャン
        ScanDirection = X_FORWARD;  // 最初の走査方向
        islandPattern();
        break;

    case STRIPE:    // ストライプスキャン
        ScanDirection = Y_FORWARD;  // 最初の走査方向
        stripePattern();
        break;

    default:
        break;
    }
        
}