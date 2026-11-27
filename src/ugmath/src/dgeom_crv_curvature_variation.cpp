







#include <math.h>

void DGEOM_crv_curvature_variation(double *a1, double *a2, double *a3, double *a4)
{
    double v12 = sqrt(a1[0] * a1[0] + a1[1] * a1[1] + a1[2] * a1[2]);
    if (v12 < 1.0e-10)
    {
        a4[1] = 0.0;
        a4[0] = 0.0;
        a4[2] = 0.0;
    }
    else
    {
        double v14 = v12 * v12;
        double v15 = v12 * v12 * v12;
        double v16 = a2[0] * a1[0] + a2[1] * a1[1] + a2[2] * a1[2];
        double v17 = v16 * 4.0 * v16;
        double v18 = v16 * -3.0 / (v14 * v12 * v14);
        double v19 = v17 / (v15 * v14 * v14)
            - (a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]
               + (a1[1] * a3[1] + a3[0] * a1[0] + a1[2] * a3[2])) / (v15 * v14);
        a4[0] = a2[0] * v18 + a1[0] * v19 + a3[0] * (1.0 / v15);
        a4[1] = v18 * a2[1] + v19 * a1[1] + 1.0 / v15 * a3[1];
        a4[2] = v18 * a2[2] + v19 * a1[2] + 1.0 / v15 * a3[2];
    }
}
