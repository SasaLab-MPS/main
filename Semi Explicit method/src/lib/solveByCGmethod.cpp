#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

int iMAX = ARRAY_SIZE*1.5;
int N_size = ARRAY_SIZE;     // 行列サイズ

// CG法：共役勾配法
VectorXd CG_method(MatrixXd A, VectorXd b, VectorXd x)
{
    VectorXd p(N_size), r(N_size), Ax(N_size), Ap(N_size);

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
        //printf("LOOP : %d\t Error : %g\n", i, error);
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
    return x;
}


