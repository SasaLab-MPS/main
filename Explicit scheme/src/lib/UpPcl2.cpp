#include "inputs.hpp"
#include "functions.hpp"

void UpPcl2(void)
{
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] == FLD)
        {
            Vel[i * 3] += Acc[i * 3] * DT;
            Vel[i * 3 + 1] += Acc[i * 3 + 1] * DT;
            Vel[i * 3 + 2] += Acc[i * 3 + 2] * DT;
            Pos[i * 3] += Acc[i * 3] * DT * DT;
            Pos[i * 3 + 1] += Acc[i * 3 + 1] * DT * DT;
            Pos[i * 3 + 2] += Acc[i * 3 + 2] * DT * DT;
            Acc[i * 3] = Acc[i * 3 + 1] = Acc[i * 3 + 2] = 0.0;
            ChkPcl(i);
        }
    }
}
