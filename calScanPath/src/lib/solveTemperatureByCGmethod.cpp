/*=====================================================================
  solveTemperatureByCGmethod.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  熱分布を計算
  Last update: Mar 30 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void solveTemperatureByCGmethod(void) {
    int NP = NumberOfParticles;             // 行列・ベクトルサイズ
    int iMAX = 2 * NP;                      // 最大反復計算回数
    VectorXd b(NP), x(NP);                  // Ax = b
    VectorXd p(NP), r(NP), Ap(NP);          // 中間変数
    VectorXd r0(NP), e(NP), Ae(NP);         // BiCGStab法のために追加した中間変数

    b = temperature;
    x = temperature;

    // pとrを計算 p = r := b - Ax
    r0 = b - Tmp * x; // r0:初期残差ベクトル
    r = r0;         // r:残差ベクトル
    p = r0;         // p:探索方向ベクトル

    // BiCGStab法本体
    double alpha, beta, error;
    double sigma, tau, zeta;
    sigma = r0.dot(r0);

    // 反復計算
    for (int i = 0; i < iMAX; i++) {
        // alphaの計算
        Ap = Tmp * p;
        tau = r0.dot(Ap);
        alpha = sigma / tau;

        // zeta, sigmaの計算
        e = r - alpha * Ap;
        Ae = Tmp * e;
        zeta = e.dot(Ae) / Ae.dot(Ae);
        x += alpha * p + zeta * e;
        r = e - zeta * Ae;
        sigma = r.dot(r0);

        // betaの計算
        beta = sigma / (tau * zeta);
        p = r + beta * (p - zeta * Ap);

        //　誤差の計算・評価
        error = r.norm() / b.norm();
        // 誤差が許容範囲以下か?
        if (error < cgEPS) {
            break;
        }
    }

    // 解の代入
    temperature = x; // 答え
}