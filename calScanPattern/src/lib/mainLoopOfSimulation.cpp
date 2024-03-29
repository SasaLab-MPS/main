/*=====================================================================
  mainLoopOfSimulation.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  シミュレーションメインループ
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void mainLoopOfSimulation(void)
{
    int iTimeStep = 0; // タイムステップカウント

    /*
    writeData_inVtuFormat();
    writeData_inProfFormat();
    */

    calNumberDensity();

    while (1)
    {
        // 粒子法計算メイン
        calGravity();
        calViscosity();

        calScanPath(STRIPE);                    // レーザ走査経路を計算

        calTemperature();                       // 温度分布を計算  
        moveParticle();
        collision();                            // 剛体衝突判定：粒子同士の異常接近防止のため

        /*
        calSurfaceTension();
        calPressure();
        calPressureGradient();
        moveParticleUsingPressureGradient();    // 粒子位置の修正
        */

        // 20ステップ毎に計算結果をファイルに出力
        if ((iTimeStep % OUTPUT_INTERVAL) == 0)
        {
            printf("TimeStepNumber: %5d   Time: %lf(s)   NumberOfParticless: %d\n", iTimeStep, Time, NumberOfParticles);
            // writeData_inVtuFormat();            // ParaViewのファイル形式(.vtu)で出力
            // writeData_inProfFormat();           // 独自のファイル形式(.prof)で出力
            writeData_inTemperatureFormat();    // 温度をcsv出力
        }
        if (Time >= FINISH_TIME)
        {
            break;
        }

        iTimeStep++;
        Time += DT;
    }
}