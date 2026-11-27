





#include <cmath>

double DGEOM_crv_curvature(double *a1, double *a2, double *a3)
{
    double len = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    if (1.0e-10 > len)
    {
        a3[2] = 0.0;
        a3[1] = 0.0;
        a3[0] = 0.0;
        return 0.0;
    }
    double inv = 1.0 / (len * len);
    double k = (a2[0] * a1[0] + a1[1] * a2[1] + a1[2] * a2[2]) * (inv * inv);
    a3[0] = a2[0] * inv - a1[0] * k;
    a3[1] = a2[1] * inv - a1[1] * k;
    a3[2] = a2[2] * inv - a1[2] * k;
    return sqrt(a3[1] * a3[1] + a3[0] * a3[0] + a3[2] * a3[2]);
}
