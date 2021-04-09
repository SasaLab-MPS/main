/*=====================================================================
  solveCGmethod.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  CG法により高速に解を計算
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

// CG法：共役勾配法
void solveByCGmethod(void)
{
    int NP = NumberOfParticles;             // 行列・ベクトルサイズ
    int iMAX = 2*NP;                        // 最大反復計算回数
    MatrixXd A(NP, NP);                     // 係数行列
    VectorXd b(NP), x(NP);                  // Ax = bko
    VectorXd p(NP), r(NP), Ax(NP), Ap(NP);  // 中間変数

    A = coefficientMatrix;
    b = sourceTerm;
    x = pressure;

    // Axを計算
    Ax = A * x;
    // pとrを計算 p = r := b - Ax
    r = b - Ax; // r:初期勾配ベクトル
    p = r;      // p:初期残差ベクトル

    // 反復計算
    for (int i = 0; i < iMAX; i++) {
        double alpha, beta, error, r0, r1;
        // alphaを計算
        Ap = A * p;
        r0 = r.dot(r);
        alpha = r0 / p.dot(Ap);
        // x, r, errorを更新
        x += alpha * p;
        r -= alpha * Ap;
        r1 = r.dot(r);
        error = r.norm(); // 誤差

        // 誤差が許容範囲以下か?
        if (error < cgEPS) {
            break;
        }
        // betaの計算
        beta = r1 / r0;
        p = r + beta * p;
    }
    pressure = x;   // 答え
}