#include "inputs.hpp"
#include "functions.hpp"

void MkBkt(void)
{
    for (int i = 0; i < nBxyz; i++)
    {
        bfst[i] = -1;
    } // nBxyz:バケットの総数
    for (int i = 0; i < nBxyz; i++)
    {
        blst[i] = -1;
    }
    for (int i = 0; i < nP; i++)
    {
        nxt[i] = -1;
    } // nP:粒子の総数
    for (int i = 0; i < nP; i++)
    {
        if (Typ[i] == GST)
            continue;
        int ix = (int)((Pos[i * 3] - MIN_X) * DBinv) + 1; // DB:バケット一辺の長さ，DBinv:バケット一辺の長さの逆数
        int iy = (int)((Pos[i * 3 + 1] - MIN_Y) * DBinv) + 1;
        int iz = (int)((Pos[i * 3 + 2] - MIN_Z) * DBinv) + 1;
        int ib = iz * nBxy + iy * nBx + ix; // ib:粒子iが属するバケットの通し番号
        int j = blst[ib];                   // blstの最初の粒子番号を上書きしないように避難
        blst[ib] = i;
        if (j == -1)
        {
            bfst[ib] = i;
        }
        else
        {
            nxt[j] = i;
        }
    }
}
