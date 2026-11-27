








#include <math.h>

double MC_signed_dist_plane_axis(double* const n, double d,
                                 double* const pt, double* const axis)
{
    if (!(fabs(n[1] * pt[1] + n[0] * pt[0] + n[2] * pt[2]) < 0.0001))
        return 0.0;
    return n[1] * axis[1] + n[0] * axis[0] + n[2] * axis[2] - d;
}
