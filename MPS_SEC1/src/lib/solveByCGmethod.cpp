/*=====================================================================
  solveCGmethod.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  CG法により高速に解を計算する関数
  Last update: Feb 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

// CG法：共役勾配法
void solveByCGmethod(void)
{
    int NoP = NumberOfParticles; // 行列サイズ
    int iMAX = 2*NoP;
    MatrixXd A(NoP, NoP);
    VectorXd b(NoP), x(NoP), p(NoP), r(NoP), Ax(NoP), Ap(NoP);

    A = coefficientMatrix;
    b = sourceTerm;
    x = pressure;

    // Axを計算
    Ax = A * x;
    // pとrを計算 p = r := b - Ax
    p = b - Ax; // p:初期勾配ベクトル
    r = p;      // 初期残差ベクトル

    // 反復計算
    for (int i = 0; i < iMAX; i++)
    {
        double alpha, beta, error = 0;
        // alphaを計算
        Ap = A * p;
        alpha = p.dot(r) / p.dot(Ap);
        // x, rを更新
        x += alpha * p;
        r -= alpha * Ap;
        // 誤差を計算
        error = r.norm();
        if (error < cgEPS)
        {
            break;
        }
        else
        {
            // betaの計算
            beta = -r.dot(Ap) / p.dot(Ap);
        }
        p = r + beta * p;
    }
    pressure = x;
}