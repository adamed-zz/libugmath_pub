






#include <cmath>

bool MC_q_perp(double* const a, double* const b)
{
    return fabs(a[1] * b[1] + a[0] * b[0] + a[2] * b[2]) < 0.0001;
}
