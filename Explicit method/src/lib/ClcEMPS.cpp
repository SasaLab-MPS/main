#include "inputs.hpp"
#include "functions.hpp"

void ClcEMPS(void)
{
    while (1)
    {
        if (iLP % 100 == 0)
        {
            int p_num = 0;
            for (int i = 0; i < nP; i++)
            {
                if (Typ[i] != GST)
                    p_num++;
            }
            printf("%5d th TIM: %lf / p_num: %d\n", iLP, TIM, p_num);
        }
        if (iLP % OPT_FQC == 0)
        {
            WrtDat();
            if (TIM >= FIN_TIM)
            {
                break;
            }
        }
        MkBkt();
        VscTrm();
        UpPcl1();
        ChkCol();
        MkPrs();
        PrsGrdTrm();
        UpPcl2();
        MkPrs();
        for (int i = 0; i < nP; i++)
        {
            pav[i] += Prs[i];
        }
        iLP++;
        TIM += DT;
    }
}
