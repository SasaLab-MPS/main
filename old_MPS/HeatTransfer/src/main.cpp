#include "../include/inputs.hpp"
#include "../include/functions.hpp"

// 液体領域の指定
//double x_width = 0.25, y_height = 0.5, z_depth = 0.3;

int main(int argc, char **argv)
{
    printf("\n*** START PARTICLE-SIMULATION ***\n");
    if (DIM == 2)
    {
        initializeParticlePositionAndVelocity_for2dim();
    }
    else
    {
        initializeParticlePositionAndVelocity_for3dim();
    }
    calConstantParameter();
    mainLoopOfSimulation();
    printf("*** END ***\n\n");
    return 0;
}