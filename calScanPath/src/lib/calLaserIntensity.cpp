/*=====================================================================
  calLaserRadiation.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double calLaserIntensity(Particle P)
{   
    double power = DT * LASER_POWER;    // レーザ出力，WからJに変換
    double intensity = 0.0;
    double a = 0.5 * LASER_DIAMETER;    // レーザ半径，ガウス分布のσに相当

    // 強度計算
    double rx, ry;  // レーザ中心からの距離
    double r, r2;   // 中間変数
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

    if (DIM == 2) {
        P.z = 0.0;
    } else {
        P.z = z_MAX;
    }
    
    return intensity;
}