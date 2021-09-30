/*=====================================================================
  calPowderHeatTrancefer.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  粉末の熱伝導率を計算
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

double calPowderHeatTrancefer(double tmp) {
    double kp;              // 粉末の熱伝導率 (W/mK)
    double kg = 0.0187;     // アルゴンガスの熱伝導率 @50℃ (W/mK)
    double ks = HEAT_CONDUCTIVITY; // 個体の熱伝導率 (W/mK)
    double phi = 0.5;       // 粉末の空隙率

    double F0 = 1/3;        // 輻射パラメータ
    double Dp = 34.9*10e-6; // 粉末の平均粒径 (m)
    double epsiron = 0.1;   // アルミニウムの酸化面として
   
    double kr;              // レーザ照射による紛体の熱特性
    double sigmaR = epsiron * STEFAN_BOLTZMANN_CONSTANT; // 輻射率：放射率 × ステファン・ボルツマン定数
    kr = 4*F0*sigmaR*Dp*pow(tmp, 3.0);

    // 粉末の熱伝導率を計算
    double kgs = kg/ks;
    kp = kg*( (1-sqrt(1-phi))*(1+phi*kr/kg) + sqrt(1-phi)*(2/(1-kgs)*(1/(1-kgs)*log(ks/kg)-1)+kr/kg) ) ;

    return kp;
}