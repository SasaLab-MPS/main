/*=====================================================================
  solveSimultaniousEquationsByGaussEliminationMethod.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  掃き出し法を用いて圧力に関する連立方程式の解を計算
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void solveSimultaniousEquationsByGaussEliminationMethod(void)
{
    int i, j, k;
    double c;
    double sumOfTerms;
    int n = NumberOfParticles;

    // 圧力を0 Paで初期化
    for (i = 0; i < n; i++)
    {
        Pressure[i] = 0.0;
    }

    // 前進消去
    for (i = 0; i < n - 1; i++)
    {
        if (BoundaryCondition[i] != INNER_PARTICLE)
            continue;
        for (j = i + 1; j < n; j++)
        {
            if (BoundaryCondition[j] == GHOST_OR_DUMMY)
                continue;
            c = CoefficientMatrix[j * n + i] / CoefficientMatrix[i * n + i];
            for (k = i + 1; k < n; k++)
            {
                CoefficientMatrix[j * n + k] -= c * CoefficientMatrix[i * n + k];
            }
            SourceTerm[j] -= c * SourceTerm[i];
        }
    }

    // 後退代入
    for (i = n - 1; i >= 0; i--)
    {
        if (BoundaryCondition[i] != INNER_PARTICLE)
            continue;
        sumOfTerms = 0.0;
        for (j = i + 1; j < n; j++)
        {
            if (BoundaryCondition[j] == GHOST_OR_DUMMY)     // 自由表面での圧力計算を省略(自由表面では圧力が既知のため)
                continue;
            sumOfTerms += CoefficientMatrix[i * n + j] * Pressure[j];
        }
        Pressure[i] = (SourceTerm[i] - sumOfTerms) / CoefficientMatrix[i * n + i];
    }
}
