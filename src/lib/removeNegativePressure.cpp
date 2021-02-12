/*=====================================================================
  removeNegativePressure.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  0 Pa未満の圧力が発生した場合0 Paに修正
  Last update: Feb 12, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void removeNegativePressure(void)
{
    int i;

    for (i = 0; i < NumberOfParticles; i++)
    {
        if (Pressure[i] < 0.0)
            Pressure[i] = 0.0;
    }
}
