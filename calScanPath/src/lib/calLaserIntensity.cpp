/*=====================================================================
  calLaserRadiation.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double calLaserIntensity(Position P)
{
    //cout << "call calLaserIntensity" << endl;
    
    double power = DT * LASER_POWER;    // レーザ出力，WからJに変換
    double intensity = 0.0;
    double a = 0.5 * LASER_DIAMETER;    // レーザ半径，ガウス分布のσに相当

    double rx, ry;  // レーザ中心からの距離
    double r, r2;   // 中間変数
    // 強度計算
    if (P.z == z_MAX) {
        rx = P.x - centerOfLaser.x;
        ry = P.y - centerOfLaser.y;
        r2 = rx * rx + ry * ry;
        r = sqrt(r2);

        if (r < 3.1 * a) {
            // レーザ強度の計算
            intensity = (power / (M_PI * a * a)) * exp((-1) * r2 / (a * a));
            // 面積当たりの投入エネルギーに変換
            intensity *= (PARTICLE_DISTANCE * PARTICLE_DISTANCE);
        }       
    }
    return intensity;
}