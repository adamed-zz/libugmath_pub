






#include <math.h>

double MC_dist(double* const a, double* const b)
{
    return sqrt((a[0] - b[0]) * (a[0] - b[0])
              + (a[1] - b[1]) * (a[1] - b[1])
              + (a[2] - b[2]) * (a[2] - b[2]));
}
