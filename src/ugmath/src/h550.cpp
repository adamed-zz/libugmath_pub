









#include <math.h>

extern int eqz(const double* a1, const double* a2, const int* a3);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h550(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, int const* a7, double* a8)
{
    int m = *a7;
    double v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19;
    if (m == 2)
    {
        v8 = *a1 - *a2;
        v9 = a1[1] - a2[1];
        v10 = a1[2] - a2[2];
        v11 = *a3 - *a2;
        v12 = a3[1] - a2[1];
        v13 = a3[2] - a2[2];
        v14 = *a3 - *a1;
        v15 = a3[1] - a1[1];
        v16 = a3[2] - a1[2];
        v17 = *a6 - *a5;
        v18 = *a6 - *a4;
        v19 = *a4 - *a5;
    }
    else if (m == 3)
    {
        v8 = *a1 - *a3;
        v9 = a1[1] - a3[1];
        v10 = a1[2] - a3[2];
        v11 = *a2 - *a3;
        v12 = a2[1] - a3[1];
        v13 = a2[2] - a3[2];
        v14 = *a2 - *a1;
        v15 = a2[1] - a1[1];
        v16 = a2[2] - a1[2];
        v17 = *a5 - *a6;
        v18 = *a5 - *a4;
        v19 = *a4 - *a6;
    }
    else
    {
        v8 = *a2 - *a1;
        v9 = a2[1] - a1[1];
        v10 = a2[2] - a1[2];
        v11 = *a3 - *a1;
        v12 = a3[1] - a1[1];
        v13 = a3[2] - a1[2];
        v14 = *a3 - *a2;
        v15 = a3[1] - a2[1];
        v16 = a3[2] - a2[2];
        v17 = *a6 - *a4;
        v18 = *a6 - *a5;
        v19 = *a5 - *a4;
    }
    double v26 = v17;
    double v24 = v19;
    double v25 = v18;
    double v20, v21, v22;
    if (eqz(&v24, &kZero, &kMode0) || eqz(&v26, &kZero, &kMode0) || eqz(&v25, &kZero, &kMode0))
    {
        v20 = 0.0;
        v21 = 0.0;
        v22 = 0.0;
    }
    else
    {
        v20 = v13 / v26 + v10 / v24 - v16 / v25;
        v21 = v12 / v26 + v9 / v24 - v15 / v25;
        v22 = v11 / v26 + v8 / v24 - v14 / v25;
    }
    double* v23 = a8;
    v23[0] = v22;
    v23[1] = v21;
    v23[2] = v20;
}
