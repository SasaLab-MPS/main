/*=====================================================================
  calConstantParameter.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  
  Last update: Feb 11, 2021
=======================================================================*/
#include "../inputs.hpp"
#include "../functions.hpp"

void calConstantParameter(void)
{

    Re_forNumberDensity = RADIUS_FOR_NUMBER_DENSITY;
    Re_forGradient = RADIUS_FOR_GRADIENT;
    Re_forLaplacian = RADIUS_FOR_LAPLACIAN;
    Re2_forNumberDensity = Re_forNumberDensity * Re_forNumberDensity;
    Re2_forGradient = Re_forGradient * Re_forGradient;
    Re2_forLaplacian = Re_forLaplacian * Re_forLaplacian;
    calNZeroAndLambda();
    FluidDensity = FLUID_DENSITY;
    collisionDistance = COLLISION_DISTANCE;
    collisionDistance2 = collisionDistance * collisionDistance;
    FileNumber = 0;
    Time = 0.0;
}
