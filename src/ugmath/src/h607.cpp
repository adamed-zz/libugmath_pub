










#include <math.h>

extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h607(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7, double* a8)
{
    double* v8 = a8;
    double v11 = a3[1];
    double v12 = *a2 - *a1;
    double v13 = a2[1] - a1[1];
    double v14 = *a3 - *a4;
    double v15 = *a3 - *a1;
    double v16 = v11 - a4[1];
    double v17 = v11 - a1[1];
    double den = v16 * v12 - v14 * v13;
    h805(&den, &kZero, &kMode0, a5);
    int old = *a5;
    *a5 = 1 - *a5;
    if (old != 1)
    {
        double v19 = v17 * v14;
        double v20 = (v17 * v12 - v15 * v13) / den;
        *a6 = (v15 * v16 - v19) / den;
        *a7 = v20;
        v8[0] = (*a2 - *a1) * *a6 + *a1;
        v8[1] = (a2[1] - a1[1]) * *a6 + a1[1];
    }
}
