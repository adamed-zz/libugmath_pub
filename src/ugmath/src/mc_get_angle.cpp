











#include <math.h>

double MC_get_angle(double* const a, double* const b)
{
    double dot = a[1] * b[1] + a[0] * b[0] + a[2] * b[2];
    if (dot > 0.9999999000000001)
        return 0.0;
    if (dot < -0.9999999000000001)
        return 3.141592653589793;
    return acos(dot);
}
