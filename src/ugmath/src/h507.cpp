








#include <math.h>

extern void h053(const double* a1, const double* a2, double* a3);

void h507(const double* a1, const double* a2, const double* a3, double* a4, double* a5, int* a6)
{
    *a6 = 1;
    double v9 = *a2;
    double v10 = *a3;
    double v11 = a2[1];
    double v21 = a1[1] - v11;
    double dx = *a1 - *a2;
    double v13 = sqrt(v21 * v21 + dx * dx);

    if (!(v10 >= v13))
    {
        double v22;
        h053(&v21, &dx, &v22);
        double v14 = v13 * v13 - v10 * v10;
        double v15 = sqrt(v14);
        double v16 = atan(v15 / v10);
        double v17 = v16 + v22;
        double v18 = v22 - v16;
        a4[0] = cos(v22 - v16) * v10 + v9;
        a4[1] = sin(v18) * v10 + v11;
        a4[2] = a2[2];
        double v19 = cos(v17);
        a5[0] = v19 * v10 + v9;
        a5[1] = sin(v17) * v10 + v11;
        a5[2] = a2[2];
    }
    else
    {
        *a6 = 0;
    }
}
