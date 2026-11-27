








#include <math.h>

double bc_POLE_3d_distance(double *const a1, double *const a2, double *const a3)
{
    double dz = a1[2] / a1[3] - a2[2] / a2[3];
    double dx = a1[0] / a1[3] - a2[0] / a2[3];
    double dy = a1[1] / a1[3] - a2[1] / a2[3];
    a3[0] = dx;
    a3[1] = dy;
    a3[2] = dz;
    return sqrt(dx * dx + dy * dy + dz * dz);
}
