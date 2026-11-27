









#include <math.h>

void h616(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v4, v5, v6, v7, v8, v9, v10, v11, v12;
    v4 = *a2 - *a1;
    v5 = a2[1] - a1[1];
    v6 = a2[2] - a1[2];
    v7 = v4;
    if (v4 < 0.0)
        v7 = -v4;
    v8 = -v4;
    v9 = a2[1] - a1[1];
    if (v5 < 0.0)
        v9 = -v5;
    v10 = -v5;
    if (v7 > v9)
    {
        if (v4 >= 0.0)
            v8 = *a2 - *a1;
        v11 = a2[2] - a1[2];
        if (v6 < 0.0)
            v11 = -v6;
        if (v11 < v8)
        {
            *a4 = (*a3 - *a1) / v4;
            return;
        }
        goto LABEL_17;
    }
    if (v5 >= 0.0)
        v10 = a2[1] - a1[1];
    v12 = a2[2] - a1[2];
    if (v6 < 0.0)
        v12 = -v6;
    if (v12 >= v10)
    {
    LABEL_17:
        *a4 = (a3[2] - a1[2]) / v6;
        return;
    }
    *a4 = (a3[1] - a1[1]) / v5;
}
