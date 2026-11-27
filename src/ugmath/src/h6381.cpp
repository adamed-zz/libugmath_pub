





#include <math.h>

void h806(const double* a1, const double* a2, const double* a3, int* a4);

namespace {
const double kZero = 0.0;
const double kTol = 1.0e-10;
}

void h6381(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    double v12 = (a3[1] - a1[1]) * a2[1] + (*a3 - *a1) * a2[0] + (a3[2] - a1[2]) * a2[2];

    h806(&v12, &kZero, &kTol, a4);
    double v10;
    if (*a4)
    {
        *a4 = 0;
        v10 = 0.0;
    }
    else
    {
        double v8 = sqrt(a2[0] * a2[0] + a2[1] * a2[1] + a2[2] * a2[2]);
        *a5 = v12 / v8;
        *a4 = -1;
        v10 = *a5;
        bool v11 = *a5 < 0.0;
        if (*a5 > 0.0)
        {
            *a4 = 1;
            v10 = *a5;
            v11 = *a5 < 0.0;
        }
        if (v11)
        {
            *a5 = -v10;
            return;
        }
    }
    *a5 = v10;
}
