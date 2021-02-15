#include "inputs.hpp"
#include "functions.hpp"

void ChkPcl(int i)
{
    if (Pos[i * 3] > MAX_X || Pos[i * 3] < MIN_X ||
        Pos[i * 3 + 1] > MAX_Y || Pos[i * 3 + 1] < MIN_Y ||
        Pos[i * 3 + 2] > MAX_Z || Pos[i * 3 + 2] < MIN_Z)
    {
        Typ[i] = GST;
        Prs[i] = Vel[i * 3] = Vel[i * 3 + 1] = Vel[i * 3 + 2] = 0.0;
    }
}
