#include "inputs.hpp"
#include "functions.hpp"

int main(int argc, char **argv)
{
    printf("start emps.\n");
    RdDat();
    AlcBkt();
    SetPara();

    double timer_sta = get_dtime();

    ClcEMPS();

    double timer_end = get_dtime();
    printf("Total        : %13.6lf sec\n", timer_end - timer_sta);

    free(Acc);
    free(Pos);
    free(Vel);
    free(Prs);
    free(pav);
    free(Typ);
    free(bfst);
    free(blst);
    free(nxt);
    printf("end emps.\n");
    return 0;
}