/*=====================================================================
  calScangPath.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

Coordinate calScangPath(string strategy, double length)
{
    /* レーザの中心座標を返すようにした方が良いか? */
    Coordinate centerOfLaser;                       // レーザの中心座標

    double travelDistance = Time * SCAN_SPEED;      // 合計の走査距離
    double h = SCAN_PITCH;

    int totalRepetition = travelDistance / length;  // レーザが折り返した総数
    
    int nx;     // x 方向に繰り返せる最大数
    int ny;     // y 方向に繰り返せる最大数

    int k, l, m;

    double y = (double)m * h;

    if (strategy == "Stripe")
    {
        /* code */
    }
    else if (strategy == "Island") {
        ny = y_MAX / h;
        m = totalRepetition / ny;       // 短冊の総数
        k = totalRepetition - m * ny;   // そのストライプの中でレーザが行き来した回数
        
        /* レーザの中心座標の計算 */
        double tx = travelDistance - (double)totalRepetition * length;
        double ty = (double)k * h;
        // x 座標の計算
        if (k % 2 == 1) {
            centerOfLaser.x = (double)(m+1) * length - tx;
        } else {
            centerOfLaser.x = (double)m * length + tx;
        }
        // y 座標の計算
        if (tx > 0 && tx < y_MAX) {
            centerOfLaser.y = ty + h;
        } else {
            centerOfLaser.y = ty;
        }
        
        centerOfLaser.z = z_MAX;
    }
    else {
        /* code */
    }

    return centerOfLaser;
}