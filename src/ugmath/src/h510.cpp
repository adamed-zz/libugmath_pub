









#include <math.h>

extern void h300(const double* a1, const double* a2, double* a3);
extern int eqz(const double* a1, const double* a2, const int* a3);
extern void h402(const double* a1, const double* a2, const double* a3, double* a4);
extern void h203(const double* a1, const double* a2, const double* a3, int* a4);

static const double kOne = 1.0;
static const double kZero = 0.0;
static const int kMode0 = 0;
static const int kMode1 = 1;

void h510(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6)
{
    double c[3];
    c[0] = a3[0];
    c[1] = a3[1];
    c[2] = a3[2];
    double v19;
    h300(c, a1, &v19);
    double v20 = v19 / (*a2 * *a2);
    if (eqz(&v20, &kOne, &kMode0))
    {
        *a5 = 2;
    }
    else
    {
        if (eqz(&v19, &kZero, &kMode1))
        {
            c[0] = a4[0];
            c[1] = a4[1];
            c[2] = a4[2];
        }
        double* v9 = a6;
        h402(a1, a2, c, a6);
        *a5 = 1;
        double v17[2];
        v17[0] = a1[0] + a1[0] - v9[0];
        v17[1] = a1[1] + a1[1] - v9[1];
        int v18;
        h203(v9, v17, a4, &v18);
        if (v18 == 2)
        {
            v9[0] = v17[0];
            v9[1] = v17[1];
        }
    }
}
