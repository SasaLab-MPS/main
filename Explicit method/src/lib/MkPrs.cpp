#include "inputs.hpp"
#include "functions.hpp"

void MkPrs(void)
{
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] != GST)
        {
            double pos_ix = Pos[i * 3];
            double pos_iy = Pos[i * 3 + 1];
            double pos_iz = Pos[i * 3 + 2];
            double ni = 0.0;
            // 中心のバケットの決定
            int ix = (int)((pos_ix - MIN_X) * DBinv) + 1;
            int iy = (int)((pos_iy - MIN_Y) * DBinv) + 1;
            int iz = (int)((pos_iz - MIN_Z) * DBinv) + 1;
            for (int jz = iz - 1; jz <= iz + 1; jz++)
            { // 3*3*3の範囲を探索
                for (int jy = iy - 1; jy <= iy + 1; jy++)
                {
                    for (int jx = ix - 1; jx <= ix + 1; jx++)
                    {
                        int jb = jz * nBxy + jy * nBx + jx;
                        int j = bfst[jb];
                        if (j == -1)
                            continue; // バケット内に粒子が存在しない
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
                                    ni += w;
                                }
                            }
                            j = nxt[j];
                            if (j == -1)
                                break;
                        }
                    }
                }
            }
            double mi = Dns[Typ[i]];
            double pressure = (ni > n0) * (ni - n0) * A2 * mi;
            Prs[i] = pressure;
        }
    }
}
