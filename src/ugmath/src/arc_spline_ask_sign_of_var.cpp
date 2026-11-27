






#include <math.h>

int ARC_SPLINE_ask_sign_of_var(double v, double tol)
{
    if (tol >= fabs(v - 0.0))
        return 0;
    if (v > 0.0)
        return 1;
    return -1;
}
