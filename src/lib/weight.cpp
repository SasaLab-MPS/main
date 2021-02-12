/*=====================================================================
  weight.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  重み関数の計算
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

double weight(double distance, double re)
{
    /* re:影響半径 */
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