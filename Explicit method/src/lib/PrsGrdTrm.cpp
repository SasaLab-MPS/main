#include "inputs.hpp"
#include "functions.hpp"

void PrsGrdTrm(void)
{
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] == FLD)
        {
            double Acc_x = 0.0;
            double Acc_y = 0.0;
            double Acc_z = 0.0;
            double pos_ix = Pos[i * 3];
            double pos_iy = Pos[i * 3 + 1];
            double pos_iz = Pos[i * 3 + 2];
            double pre_min = Prs[i];
            int ix = (int)((pos_ix - MIN_X) * DBinv) + 1;
            int iy = (int)((pos_iy - MIN_Y) * DBinv) + 1;
            int iz = (int)((pos_iz - MIN_Z) * DBinv) + 1;
            for (int jz = iz - 1; jz <= iz + 1; jz++)
            {
                for (int jy = iy - 1; jy <= iy + 1; jy++)
                {
                    for (int jx = ix - 1; jx <= ix + 1; jx++)
                    {
                        int jb = jz * nBxy + jy * nBx + jx;
                        int j = bfst[jb];
                        if (j == -1)
                            continue;
                        for (;;)
                        {
                            double v0 = Pos[j * 3] - pos_ix;
                            double v1 = Pos[j * 3 + 1] - pos_iy;
                            double v2 = Pos[j * 3 + 2] - pos_iz;
                            double dist2 = v0 * v0 + v1 * v1 + v2 * v2;
                            if (dist2 < r2)
                            {
                                if (j != i && Typ[j] != GST)
                                {
                                    if (pre_min > Prs[j])
                                        pre_min = Prs[j];
                                }
                            }
                            j = nxt[j];
                            if (j == -1)
                                break;
                        }
                    }
                }
            }
            for (int jz = iz - 1; jz <= iz + 1; jz++)
            {
                for (int jy = iy - 1; jy <= iy + 1; jy++)
                {
                    for (int jx = ix - 1; jx <= ix + 1; jx++)
                    {
                        int jb = jz * nBxy + jy * nBx + jx;
                        int j = bfst[jb];
                        if (j == -1)
                            continue;
                        for (;;)
                        {
                            double v0 = Pos[j * 3] - pos_ix;
                            double v1 = Pos[j * 3 + 1] - pos_iy;
                            double v2 = Pos[j * 3 + 2] - pos_iz;
                            double dist2 = v0 * v0 + v1 * v1 + v2 * v2;
                            if (dist2 < r2)
                            {
                                if (j != i && Typ[j] != GST)
                                {
                                    double dist = sqrt(dist2);
                                    double w = WEI(dist, r);
                                    w *= (Prs[j] - pre_min) / dist2;
                                    Acc_x += v0 * w;
                                    Acc_y += v1 * w;
                                    Acc_z += v2 * w;
                                }
                            }
                            j = nxt[j];
                            if (j == -1)
                                break;
                        }
                    }
                }
            }
            Acc[i * 3] = Acc_x * invDns[FLD] * A3;
            Acc[i * 3 + 1] = Acc_y * invDns[FLD] * A3;
            Acc[i * 3 + 2] = Acc_z * invDns[FLD] * A3;
        }
    }
}
