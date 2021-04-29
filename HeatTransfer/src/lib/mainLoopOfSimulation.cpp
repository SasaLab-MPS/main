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

    writeData_inVtuFormat();
    writeData_inProfFormat();
    
    while (1)
    {
        // 粒子法計算メイン
        calGravity();
        calViscosity();

        setTemperatureDistribution();           // 初期温度分布を設定
        //setMinimumTemperature();                // 粒子i周辺の最低温度を計算
        calTemperature();                       // 温度分布を計算
        
        moveParticle();
        collision();                            // 剛体衝突判定：粒子同士の異常接近防止のため
        calPressure();
        calPressureGradient();
        moveParticleUsingPressureGradient();    // 粒子位置の修正

        iTimeStep++;
        Time += DT;

        // 20ステップ毎に計算結果をファイルに出力
        if ((iTimeStep % OUTPUT_INTERVAL) == 0)
        {
            printf("TimeStepNumber: %4d   Time: %lf(s)   NumberOfParticless: %d\n", iTimeStep, Time, NumberOfParticles);
            writeData_inVtuFormat();  // ParaViewのファイル形式(.vtu)で出力
            writeData_inProfFormat(); // 独自のファイル形式(.prof)で出力
        }
        if (Time >= FINISH_TIME)
        {
            break;
        }
    }
}