/*=====================================================================
  writeData_inProfFormat.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算結果の出力(独自ファイル形式)
  Last update: Feb 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void writeData_inProfFormat(void)
{
    int i;
    FILE *fp;
    char fileName[256];
    sprintf(fileName, "./prof/output_%04d.prof", FileNumber);
    fp = fopen(fileName, "w");
    fprintf(fp, "%lf\n", Time);
    fprintf(fp, "%d\n", NumberOfParticles);
    for (i = 0; i < NumberOfParticles; i++)
    {
      fprintf(fp, "%d %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", position[i].particleType, position[i].x, position[i].y, position[i].z, velocity[i].x, velocity[i].y, velocity[i].z, pressure(i), numberDensity[i], temperature[i]);
    }
    fclose(fp);
    FileNumber++;
}