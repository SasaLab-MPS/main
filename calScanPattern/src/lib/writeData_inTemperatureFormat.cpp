/*=====================================================================
  writeData_inTemperatureFormat.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算結果の出力(csvファイル形式)
  Last update: Sep 22, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void writeData_inTemperatureFormat(void)
{
    int i;
    FILE *fp;
    char fileName[256];
    sprintf(fileName, "./csv/temperature_%05d.csv", FileNumber);
    fp = fopen(fileName, "w");

    for (i = 0; i < NumberOfParticles; i++)
    {
      if (particle[i].z == z_MAX) {
        fprintf(fp, "%lf %lf %lf %lf\n", particle[i].x, particle[i].y, particle[i].z, temperature(i));
      }
    }
    fclose(fp);
    FileNumber++;
}