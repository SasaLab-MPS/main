#include "inputs.hpp"
#include "functions.hpp"

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