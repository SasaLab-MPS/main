/*=====================================================================
  deltaFunction.cpp   
  Yota INOUE (2021) 
  デルタ関数
  Last update: May 12, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double deltaFunction(double phi) {
    double epsilon = 3.1 * RADIUS_FOR_LAPLACIAN;
    double delta;

    if (phi < epsilon) {
        delta = 1 + cos(M_PI * phi / epsilon);
    } else {
        delta = 0;
    }
    
    return delta;
}