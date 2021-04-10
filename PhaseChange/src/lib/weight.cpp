/*=====================================================================
  weight.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  重み関数の計算
  Last update: Feb 21, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double weight(double distance, double re)
{
    double weightIJ;

    if (distance >= re)
    {
        weightIJ = 0.0;
    }
    else
    {
        weightIJ = (re / distance) - 1.0;
    }
    return weightIJ;
}