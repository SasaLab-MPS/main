/*=====================================================================
  solvePressureByCGmethod.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  BiCGStab法により高速に解を計算(非対称行列にも対応)
  Last update: May 31, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

// CG法：共役勾配法
void solvePressureByCGmethod(void)
{
    int NP = NumberOfParticles;             // 行列・ベクトルサイズ
    int iMAX = 2*NP;                        // 最大反復計算回数
    SparseMatrix<double> A(NP, NP);         // 係数行列
    VectorXd b(NP), x(NP);                  // Ax = b (xを求める)
    VectorXd p(NP), r(NP), Ap(NP);          // 中間変数
    VectorXd r0(NP), e(NP), Ae(NP);         // BiCGStab法のために追加した中間変数

    A = coefficientMatrix;
    b = sourceTerm;
    x = pressure;

    // pとrを計算 p = r := b - Ax
    r0 = b - A * x; // r0:初期残差ベクトル
    r = r0;         // r:残差ベクトル
    p = r0;         // p:探索方向ベクトル

    // BiCGStab法本体
    double alpha, beta, error;
    double sigma, tau, zeta;
    sigma = r0.dot(r0);

    // 反復計算
    for (int i = 0; i < iMAX; i++) {
        // alphaの計算
        Ap = A * p;
        tau = r0.dot(Ap);
        alpha = sigma / tau;

        // zeta, sigmaの計算
        e = r - alpha * Ap;
        Ae = A * e;
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
    pressure = x;   // 答え
}