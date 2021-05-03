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
    int NP = NumberOfParticles;            // 行列・ベクトルサイズ
    int iMAX = 2 * NP;                     // 最大反復計算回数
    SparseMatrix<double> A(NP, NP);        // 係数行列(疎行列)
    VectorXd b(NP), x(NP);                 // Ax = b
    VectorXd p(NP), r(NP), Ax(NP), Ap(NP); // 中間変数

    A.setFromTriplets(Aij.begin(), Aij.end());
    b = temperature;
    //x = temperature;

    // Axを計算
    Ax = A * x;
    // pとrを計算 p = r := b - Ax
    r = b - Ax; // r:初期勾配ベクトル
    p = r;      // p:初期残差ベクトル

    // 反復計算
    for (int i = 0; i < iMAX; i++)
    {
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
            //cout << "i:" << i << endl;
            break;
        }
        // betaの計算
        beta = r1 / r0;
        p = r + beta * p;
    }
    temperature = x; // 答え
}