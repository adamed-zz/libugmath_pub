







#include <cmath>

void h018(double *a1, int *a2, double *a3)
{
    double v5 = a1[1];
    double v7 = *a1;
    double v9 = sqrt(v5 * v5 + v7 * v7);
    double v6 = 0.0;
    if (v7 == 0.0)
    {
        if (v5 > 0.0)
            v6 = 1.5707963267948966;
        if (v7 == 0.0 && v5 < 0.0)
            v6 = 4.71238898038469;
    }
    else
    {
        v6 = atan(v5 / v7);
    }
    if (v5 == 0.0)
    {
        if (v7 < 0.0)
            v6 = 3.141592653589793;
        else
            v6 = 0.0;
    }
    if (v7 > 0.0 && v5 < 0.0)
        v6 = v6 + 6.283185307179586;
    if (v7 < 0.0)
    {
        if (v5 < 0.0)
            v6 = v6 + 3.141592653589793;
        if (v5 > 0.0)
            v6 = v6 + 3.141592653589793;
    }
    double v10 = (double)*a2;
    double v11 = v6 / v10;
    double v12 = pow(v9, 1.0 / v10);
    *a3 = cos(v11) * v12;
    a3[1] = sin(v11) * v12;
}
