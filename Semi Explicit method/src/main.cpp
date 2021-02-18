#include "../include/inputs.hpp"
#include "../include/functions.hpp"

// 計算領域の指定
double x_width = 0.25, y_height = 0.5, z_depth = 0.0;

int main(int argc, char **argv)
{
    printf("\n*** START PARTICLE-SIMULATION ***\n");
    if (DIM == 2)
    {
        initializeParticlePositionAndVelocity_for2dim(x_width, y_height);
    }
    else
    {
        initializeParticlePositionAndVelocity_for3dim(x_width, y_height, z_depth);
    }
    calConstantParameter();
    mainLoopOfSimulation();
    printf("*** END ***\n\n");
    return 0;
}