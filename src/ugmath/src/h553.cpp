









#include <math.h>

void h553(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, int const* a7, double* a8)
{
    double v8 = a2[1];
    double v9 = a2[2];
    double v10 = *a5 - *a4;
    double inv10 = 1.0 / v10;
    double v11 = -(inv10);
    double v12 = *a2 * inv10 + v11 * *a1;
    double v13 = v11 * a1[1] + v8 * inv10;
    double v14 = *a6 - *a4;
    double v15 = v11 * a1[2] + v9 * inv10;
    double v16 = *a6 - *a5;
    double v17 = v10 / v14;
    double v18 = 1.0 / v16;
    double v19 = v16 / v14;
    double v20 = v18 * *a3 + *a2 * -v18;
    double v21 = v18 * a3[1] + v8 * -v18;
    double v22 = v18 * a3[2] + v9 * -v18;
    double v23 = v13 * v19 + v21 * v17;
    double v24 = v15 * v19 + v22 * v17;
    a8[0] = v12 * v19 + v20 * v17;
    a8[1] = v23;
    a8[2] = v24;
    if (*a7 == 1)
        goto L5;
    if (*a7 == 2)
        return;
    if (*a7 != 3)
    {
    L5:
        a8[0] = v12 * 1.5 - a8[0] * 0.5;
        a8[1] = v13 * 1.5 - v23 * 0.5;
        a8[2] = v15 * 1.5 - v24 * 0.5;
    }
    else
    {
        a8[0] = v20 * 1.5 - a8[0] * 0.5;
        a8[1] = v21 * 1.5 - v23 * 0.5;
        a8[2] = v22 * 1.5 - v24 * 0.5;
    }
}
