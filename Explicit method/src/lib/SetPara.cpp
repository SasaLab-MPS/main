#include "inputs.hpp"
#include "functions.hpp"

void SetPara(void)
{
    double tn0 = 0.0;
    double tlmd = 0.0;
    for (int ix = -4; ix < 5; ix++)
    {
        for (int iy = -4; iy < 5; iy++)
        {
            for (int iz = -4; iz < 5; iz++)
            {
                double x = PCL_DST * (double)ix;
                double y = PCL_DST * (double)iy;
                double z = PCL_DST * (double)iz;
                double dist2 = x * x + y * y + z * z;
                if (dist2 <= r2)
                {
                    if (dist2 == 0.0)
                        continue;
                    double dist = sqrt(dist2);
                    tn0 += WEI(dist, r);
                    tlmd += dist2 * WEI(dist, r);
                }
            }
        }
    }
    n0 = tn0;                            //初期粒子数密度
    lmd = tlmd / tn0;                    //ラプラシアンモデルの係数λ
    A1 = 2.0 * KNM_VSC * DIM / n0 / lmd; //粘性項の計算に用いる係数
    A2 = SND * SND / n0;                 //圧力の計算に用いる係数
    A3 = -DIM / n0;                      //圧力勾配項の計算に用いる係数
    Dns[FLD] = DNS_FLD;
    Dns[WLL] = DNS_WLL;
    invDns[FLD] = 1.0 / DNS_FLD;
    invDns[WLL] = 1.0 / DNS_WLL;
    rlim = PCL_DST * DST_LMT_RAT; //これ以上の粒子間の接近を許さない距離
    rlim2 = rlim * rlim;
    COL = 1.0 + COL_RAT;
    iLP = 0;   //反復数
    iF = 0;    //ファイル番号
    TIM = 0.0; //時刻
}
