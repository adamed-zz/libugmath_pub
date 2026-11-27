











#include <math.h>

void DGEOM_crv_diff_property(double *a1, double *a2, double *a3, int a4, double *a5)
{
    a5[0] = 0.0;
    a5[1] = 0.0;
    a5[2] = 0.0;
    a5[3] = 0.0;
    a5[4] = 0.0;
    a5[5] = 0.0;
    a5[6] = 0.0;
    a5[7] = 0.0;
    a5[8] = 0.0;
    a5[9] = 0.0;
    a5[10] = 0.0;

    double len = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    if (len < 1.0e-10)
        return;

    a5[0] = a1[0] / len;
    a5[1] = a1[1] / len;
    a5[2] = a1[2] / len;

    double c1 = a1[1] * a2[2] - a1[2] * a2[1];
    double c2 = a1[0] * a2[1] - a2[0] * a1[1];
    double c3 = a2[0] * a1[2] - a1[0] * a2[2];

    double mag = sqrt(c3 * c3 + c1 * c1 + c2 * c2);
    if (mag < 1.0e-10)
        return;

    a5[9] = mag / (len * len * len);
    if (a5[9] < 1.0e-10)
    {
        a5[9] = 0.0;
        return;
    }

    a5[3] = c1 / mag;
    a5[4] = c3 / mag;
    a5[5] = c2 / mag;

    a5[6] = a5[2] * a5[4] - a5[1] * a5[5];
    a5[7] = a5[0] * a5[5] - a5[2] * a5[3];
    a5[8] = a5[1] * a5[3] - a5[0] * a5[4];

    if (a4 == 1)
    {
        double t = (a2[1] * a3[2] - a2[2] * a3[1]) * a1[0];
        t += (a3[0] * a2[2] - a2[0] * a3[2]) * a1[1];
        t += (a2[0] * a3[1] - a3[0] * a2[1]) * a1[2];
        a5[10] = t / (mag * mag);
    }
}
