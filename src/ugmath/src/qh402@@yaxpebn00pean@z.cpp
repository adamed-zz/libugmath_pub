






#include <math.h>

void h402(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v5 = *a1;
    double v8 = a3[1] - a1[1];
    double v9 = *a3 - *a1;
    double v10 = v8 * v8 + v9 * v9;
    double v11 = sqrt(v10);
    double v12 = *a2;

    if (!(v11 > 0.0))
    {
        *a4 = v5 + v12;
        a4[1] = a1[1];
    }
    else
    {
        double v13 = v12 / v11;
        *a4 = v13 * v9 + v5;
        a4[1] = v8 * v13 + a1[1];
    }
}
