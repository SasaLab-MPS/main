/*=====================================================================
  calScangPattern.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calScangPath(string strategy, double length) {
    /* レーザの中心座標を返すようにした方が良いか? */
    double p = DT * LASER_POWER;                    // レーザ出力
    double travelDistance = Time * SCAN_SPEED;      // 合計の走査距離
    int repetitionNum = travelDistance / length;    // レーザが折り返した回数
    double h = SCAN_PITCH;
    Coordinate centerOfLaser;                       // レーザの中心座標

    if (strategy == "Stripe")
    {
        /* code */
    }
    else if (strategy == "Island") {
        int n = y_MAX / h;           // y方向に繰り返せる最大数
        int m = repetitionNum % n; 
        double y = (double)m * h;
        
        // レーザの中心座標の計算
        centerOfLaser.x = travelDistance - (double)(repetitionNum / n)* length;
        centerOfLaser.y = y;
        centerOfLaser.z = z_MAX;
    }
    else {
        /* code */
    }
    
}