








#include <math.h>

void h002(double* a1, const double* a2);

void h629(const double* a1, const double* a2, double* a3)
{
    static const double kTwoPi = 6.283185307179586;
    double v11, v12;
    double v4 = *a2;
    v12 = *a1;
    v11 = v4;
    h002(&v12, &kTwoPi);
    h002(&v11, &kTwoPi);
    double v7 = v11;
    double v8 = v12;
    double v9 = v11 / 3.141592653589793;
    *a3 = *a1;
    int v10 = (int)v9;
    int v13 = (int)(v8 / -3.141592653589793);
    if (v13 < 0)
    {
        if (v13 == -1 && v10 == 1)
        {
            if (fabs(v7 - 4.71238898038469) > fabs(v8 - 4.71238898038469))
                *a3 = *a2;
        }
        else
        {
            *a3 = 0.0;
        }
    }
    else if (v10 <= 0)
    {
        if (fabs(v7 - 1.5707963267948966) > fabs(v8 - 1.5707963267948966))
            *a3 = *a2;
    }
    else
    {
        *a3 = 3.141592653589793;
    }
}
