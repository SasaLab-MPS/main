#include "inputs.hpp"
#include "functions.hpp"

void WrtDat(void)
{
    char outout_filename[256];
    sprintf(outout_filename, "output%05d.prof", iF);
    fp = fopen(outout_filename, "w");
    fprintf(fp, "%d\n", nP);
    for (int i = 0; i < nP; i++)
    {
        int a[2];
        double b[8];
        a[0] = i;
        a[1] = Typ[i];
        b[0] = Pos[i * 3];
        b[1] = Pos[i * 3 + 1];
        b[2] = Pos[i * 3 + 2];
        b[3] = Vel[i * 3];
        b[4] = Vel[i * 3 + 1];
        b[5] = Vel[i * 3 + 2];
        b[6] = Prs[i];
        b[7] = pav[i] / OPT_FQC;
        fprintf(fp, " %d %d %lf %lf %lf %lf %lf %lf %lf %lf\n", a[0], a[1], b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
        pav[i] = 0.0;
    }
    fclose(fp);
    iF++;
}
