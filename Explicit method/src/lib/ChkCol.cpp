#include "inputs.hpp"
#include "functions.hpp"

// 粒子の剛体衝突を行う関数
void ChkCol(void)
{
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] == FLD)
        {
            double mi = Dns[Typ[i]];
            double pos_ix = Pos[i * 3];
            double pos_iy = Pos[i * 3 + 1];
            double pos_iz = Pos[i * 3 + 2];
            double vec_ix = Vel[i * 3];
            double vec_iy = Vel[i * 3 + 1];
            double vec_iz = Vel[i * 3 + 2];
            double vec_ix2 = Vel[i * 3];
            double vec_iy2 = Vel[i * 3 + 1];
            double vec_iz2 = Vel[i * 3 + 2];
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
                            if (dist2 < rlim2)  // 粒子自身の半径の二乗を条件判定に用いる
                            {
                                if (j != i && Typ[j] != GST)
                                {
                                    double fDT = (vec_ix - Vel[j * 3]) * v0 + (vec_iy - Vel[j * 3 + 1]) * v1 + (vec_iz - Vel[j * 3 + 2]) * v2;
                                    if (fDT > 0.0)
                                    {
                                        double mj = Dns[Typ[j]];
                                        fDT *= COL * mj / (mi + mj) / dist2;    // 運動量の交換：完全弾性体としている
                                        vec_ix2 -= v0 * fDT;
                                        vec_iy2 -= v1 * fDT;
                                        vec_iz2 -= v2 * fDT;
                                    }
                                }
                            }
                            j = nxt[j];
                            if (j == -1)
                                break;
                        }
                    }
                }
            }
            Acc[i * 3] = vec_ix2;
            Acc[i * 3 + 1] = vec_iy2;
            Acc[i * 3 + 2] = vec_iz2;
        }
    }
    for (int i = 0; i < nP; i++)
    {
        Vel[i * 3] = Acc[i * 3];
        Vel[i * 3 + 1] = Acc[i * 3 + 1];
        Vel[i * 3 + 2] = Acc[i * 3 + 2];
    }
}
