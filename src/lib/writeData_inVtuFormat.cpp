/*=====================================================================
  writeData_inVtuFormat.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  計算結果をファイル出力(ParaViewのvtuファイル形式)
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void writeData_inVtuFormat(void)
{
    int i;
    double absoluteValueOfVelocity;
    FILE *fp;
    char fileName[1024];

    sprintf(fileName, "particle_%04d.vtu", FileNumber);
    fp = fopen(fileName, "w");
    fprintf(fp, "<?xml version='1.0' encoding='UTF-8'?>\n");
    fprintf(fp, "<VTKFile xmlns='VTK' byte_order='LittleEndian' version='0.1' type='UnstructuredGrid'>\n");
    fprintf(fp, "<UnstructuredGrid>\n");
    fprintf(fp, "<Piece NumberOfCells='%d' NumberOfPoints='%d'>\n", NumberOfParticles, NumberOfParticles);
    fprintf(fp, "<Points>\n");
    fprintf(fp, "<DataArray NumberOfComponents='3' type='Float32' Name='Position' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%lf %lf %lf\n", Position[i * 3], Position[i * 3 + 1], Position[i * 3 + 2]);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "</Points>\n");
    fprintf(fp, "<PointData>\n");
    fprintf(fp, "<DataArray NumberOfComponents='1' type='Int32' Name='ParticleType' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%d\n", ParticleType[i]);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "<DataArray NumberOfComponents='1' type='Float32' Name='Velocity' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        absoluteValueOfVelocity =
            sqrt(Velocity[i * 3] * Velocity[i * 3] + Velocity[i * 3 + 1] * Velocity[i * 3 + 1] + Velocity[i * 3 + 2] * Velocity[i * 3 + 2]);
        fprintf(fp, "%f\n", (float)absoluteValueOfVelocity);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "<DataArray NumberOfComponents='1' type='Float32' Name='pressure' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%f\n", (float)Pressure[i]);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "</PointData>\n");
    fprintf(fp, "<Cells>\n");
    fprintf(fp, "<DataArray type='Int32' Name='connectivity' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%d\n", i);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "<DataArray type='Int32' Name='offsets' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "%d\n", i + 1);
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "<DataArray type='UInt8' Name='types' format='ascii'>\n");
    for (i = 0; i < NumberOfParticles; i++)
    {
        fprintf(fp, "1\n");
    }
    fprintf(fp, "</DataArray>\n");
    fprintf(fp, "</Cells>\n");
    fprintf(fp, "</Piece>\n");
    fprintf(fp, "</UnstructuredGrid>\n");
    fprintf(fp, "</VTKFile>\n");
    fclose(fp);
}
