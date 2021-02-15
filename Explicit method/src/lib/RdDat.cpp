
#include "inputs.hpp"
#include "functions.hpp"

/* グローバル変数実体化 */
FILE *fp;
char filename[256];
int iLP, iF;
double TIM;
int nP;
double *Acc, *Pos, *Vel, *Prs, *pav;
int *Typ;
double r, r2;
double DB, DB2, DBinv;
int nBx, nBy, nBz, nBxy, nBxyz;
int *bfst, *blst, *nxt;
double n0, lmd, A1, A2, A3, rlim, rlim2, COL;
double Dns[NUM_TYP], invDns[NUM_TYP];

void RdDat(void)
{
    fp = fopen(IN_FILE, "r");
    fscanf(fp, "%d", &nP);
    printf("nP: %d\n", nP);
    Acc = (double *)malloc(sizeof(double) * nP * 3); //粒子の加速度
    Pos = (double *)malloc(sizeof(double) * nP * 3); //粒子の座標
    Vel = (double *)malloc(sizeof(double) * nP * 3); //粒子の速度
    Prs = (double *)malloc(sizeof(double) * nP);     //粒子の圧力
    pav = (double *)malloc(sizeof(double) * nP);     //時間平均された粒子の圧力
    Typ = (int *)malloc(sizeof(int) * nP);           //粒子の種類
    for (int i = 0; i < nP; i++)
    {
        int a[2];
        double b[8];
        fscanf(fp, " %d %d %lf %lf %lf %lf %lf %lf %lf %lf", &a[0], &a[1], &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7]);
        Typ[i] = a[1];
        Pos[i * 3] = b[0];
        Pos[i * 3 + 1] = b[1];
        Pos[i * 3 + 2] = b[2];
        Vel[i * 3] = b[3];
        Vel[i * 3 + 1] = b[4];
        Vel[i * 3 + 2] = b[5];
        Prs[i] = b[6];
        pav[i] = b[7];
    }
    fclose(fp);
    for (int i = 0; i < nP; i++)
    {
        ChkPcl(i);
    }
    for (int i = 0; i < nP * 3; i++)
    {
        Acc[i] = 0.0;
    }
}