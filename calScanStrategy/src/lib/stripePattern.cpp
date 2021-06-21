/*=====================================================================
  stripePattern.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  ストライプスキャンのレーザ照射点を計算
  Last update: June 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void stripePattern(void) {

    double travelDistance = Time * SCAN_SPEED; // 合計の走査距離
    double hatch = SCAN_PITCH;
    double scanVectorLength = SCAN_VECTOR_LENGTH;
    int totalRepetition = travelDistance / scanVectorLength; // レーザが折り返した総数

    int ny; // y 方向に繰り返せる最大数

    int k, l;
    double Y = y_MAX;

    ny = Y / hatch;
    l = totalRepetition / ny;     // 短冊の総数
    k = totalRepetition - l * ny; // そのストライプの中でレーザが行き来した回数

    /* レーザの中心座標の計算 */
    double tx = travelDistance - (double)totalRepetition * scanVectorLength;
    double ty = (double)k * hatch;
    // x 座標の計算
    if (k % 2 == 1)
    {
        centerOfLaser.x = (double)(l + 1) * scanVectorLength - tx;
    }
    else
    {
        centerOfLaser.x = (double)l * scanVectorLength + tx;
    }
    // y 座標の計算
    if (tx > 0 && tx < Y)
    {
        centerOfLaser.y = ty + hatch;
    }
    else
    {
        centerOfLaser.y = ty;
    }
}