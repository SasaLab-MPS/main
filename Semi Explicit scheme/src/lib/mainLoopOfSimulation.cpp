/*=====================================================================
  mainLoopOfSimulation.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  シミュレーションメインループ
  Last update: Feb 11, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

MatrixXd A;                       // 行列係数 = CoefficientMatrix
VectorXd sourceTerm, pressure;    // b:右辺係数，x:圧力の列ベクトル

void mainLoopOfSimulation(void)
{
    int iTimeStep = 0; // タイムステップカウント
    // 行列，ベクトルの設定
    int NoP = NumberOfParticles;
    // 初期化
    A.setZero(NoP, NoP);
    sourceTerm.setZero(NoP);
    pressure.setZero(NoP);

    writeData_inVtuFormat();
    writeData_inProfFormat();

    while (1)
    {
        // 粒子法計算
        calGravity();
        calViscosity();
        moveParticle();
        collision();    // 剛体衝突判定：粒子同士の異常接近防止のため
        calPressure();
        calPressureGradient();
        moveParticleUsingPressureGradient();    // 粒子位置の修正

        iTimeStep++;
        Time += DT;

        // 20ステップ毎に計算結果をファイルに出力
        if ((iTimeStep % OUTPUT_INTERVAL) == 0)
        {
            printf("TimeStepNumber: %4d   Time: %lf(s)   NumberOfParticless: %d\n", iTimeStep, Time, NumberOfParticles);
            writeData_inVtuFormat();    // ParaViewのファイル形式(.vtu)で出力
            writeData_inProfFormat();   // 独自のファイル形式(.prof)で出力
        }
        if (Time >= FINISH_TIME)
        {
            break;
        }
    }
}