








#include <math.h>

extern int eqz(const double* a1, const double* a2, const int* a3);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h600(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6)
{
    double v8 = *a2 - *a1;
    double v9 = a2[1] - a1[1];
    double v10 = *a4 - *a3;
    double v11 = a4[1] - a3[1];
    double v14 = v8 * v11 - v9 * v10;
    if (eqz(&v14, &kZero, &kMode0))
    {
        *a5 = 1;
    }
    else
    {
        double* v12 = a6;
        double v13 = ((*a3 - *a1) * v11 - (a3[1] - a1[1]) * v10) / v14;
        v12[0] = v13 * v8 + *a1;
        v12[1] = v13 * v9 + a1[1];
        *a5 = 2;
    }
}
