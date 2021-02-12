/*=====================================================================
  writeData_inProfFormat.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算結果の出力(独自ファイル形式)
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void writeData_inProfFormat(void)
{
    int i;
    FILE *fp;
    char fileName[256];

    sprintf(fileName, "output_%04d.prof", FileNumber);
    fp = fopen(fileName, "w");
    fprintf(fp, "%lf\n", Time);
    fprintf(fp, "%d\n", NumberOfParticles);
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%d %lf %lf %lf %lf %lf %lf %lf %lf\n", ParticleType[i], Position[i * 3], Position[i * 3 + 1], Position[i * 3 + 2], Velocity[i * 3], Velocity[i * 3 + 1], Velocity[i * 3 + 2], Pressure[i], NumberDensity[i]);
    }
    fclose(fp);
    FileNumber++;
}
