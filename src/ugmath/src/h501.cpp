








#include <math.h>

extern void h053(const double* a1, const double* a2, double* a3);


static const double kHalfPi = 0x1.921fb54442d18p+0;

void h501(double* const a1, double* a2, double* const a3, double* const a4, double* const a5)
{
    double v14;
    h053(a3 + 1, a3, &v14);
    double v8 = v14 + kHalfPi;
    double v9 = *a1;
    double v10 = a1[1];
    double v11 = cos(v14 + kHalfPi);
    double v12 = sin(v8);
    double* v13 = a5;
    a4[0] = v11 * *a2 + v9;
    a4[1] = v12 * *a2 + v10;
    v13[0] = v9 - v11 * *a2;
    v13[1] = v10 - v12 * *a2;
}
