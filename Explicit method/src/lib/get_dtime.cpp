#include "inputs.hpp"
#include "functions.hpp"

double get_dtime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((double)(tv.tv_sec) + (double)(tv.tv_usec) * 0.000001);
}