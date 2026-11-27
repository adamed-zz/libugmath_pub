









#include <math.h>

extern void h053(const double* a1, const double* a2, double* a3);

static const double kE0018 = 1.0e-5;

void h500(double* const a1, double* a2, double* const a3, int* a4,
          double* const a5, double* const a6)
{
    double v7 = *a3;
    double v8 = *a2;
    double v9 = a3[1];
    double v10 = *a1;
    double v11 = a1[1];
    double v25 = *a3 - *a1;
    double v26 = v9 - v11;
    double v13 = sqrt(v26 * v26 + v25 * v25);
    double v14 = v13 - v8;
    if (kE0018 >= fabs(v13 - v8))
        goto L12;
    if (v14 < 0.0)
    {
        *a4 = 1;
        return;
    }
    if (v14 == 0.0)
    {
    L12:
        double* v24 = a5;
        *a4 = 2;
        v24[0] = v7;
        v24[1] = v9;
    }
    else
    {
        *a4 = 3;
        double v27;
        h053(&v26, &v25, &v27);
        double v15 = v13 * v13 - v8 * v8;
        double v16 = sqrt(v15);
        double v17 = atan(v16 / v8);
        double v18 = v17 + v27;
        double v19 = v27 - v17;
        double v20 = cos(v17 + v27);
        double* v21 = a5;
        v21[0] = v20 * v8 + v10;
        v21[1] = sin(v18) * v8 + v11;
        double v22 = cos(v19);
        double* v23 = a6;
        v23[0] = v22 * v8 + v10;
        v23[1] = sin(v19) * v8 + v11;
    }
}
