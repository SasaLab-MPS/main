/*=====================================================================
  weightForSUrfacetension.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  表面張力計算用の重み関数
  Last update: May 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double weightForSUrfacetension(double distance, double re) {
    double weightIJ;

    if (distance >= re)
    {
        weightIJ = 0.0;
    }
    else
    {
        weightIJ = 1.0;
    }
    return weightIJ;
}