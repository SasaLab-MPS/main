#include "inputs.hpp"
#include "functions.hpp"

// 仮の位置と速度を求める関数
void UpPcl1()
{
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] == FLD)
        {
            Vel[i * 3] += Acc[i * 3] * DT;
            Vel[i * 3 + 1] += Acc[i * 3 + 1] * DT;
            Vel[i * 3 + 2] += Acc[i * 3 + 2] * DT;
            Pos[i * 3] += Vel[i * 3] * DT;
            Pos[i * 3 + 1] += Vel[i * 3 + 1] * DT;
            Pos[i * 3 + 2] += Vel[i * 3 + 2] * DT;
            Acc[i * 3] = Acc[i * 3 + 1] = Acc[i * 3 + 2] = 0.0;
            ChkPcl(i);
        }
    }
}