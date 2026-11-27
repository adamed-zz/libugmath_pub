








#include <intrin.h>

int eqz(const double* a, const double* b, const int* mode);
extern const double g_zero_a;
extern const int g_mode_a;

void h0910(const int* a1, const int* a2, const double* a3, double* a4)
{
    const int v5 = *a1;
    const int v7 = *a2;

    const double t1 = a3[v7 - v5];
    _ReadWriteBarrier();
    const double t2 = a3[v5 - 1];
    double v11 = t1 - t2;
    double v8 = t2;
    if (v7 >= 1)
    {
        for (int i = 0; i < v7; ++i)
        {
            double v10;
            if (eqz(&v11, &g_zero_a, &g_mode_a))
                v10 = 0.0;
            else
                v10 = (a3[i] - v8) / v11;
            a4[i] = v10;
        }
    }
}

extern const double g_zero_a;
extern const int g_mode_a;
const double g_zero_a = 0.0;
const int g_mode_a = 0;
