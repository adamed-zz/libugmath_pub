#include <cmath>
void h206(double* a1, double* a2, double* a3, int* a4)
{
    double v4 = a1[1] - a2[1];
    double v5 = *a1 - *a2;
    volatile int* va = (volatile int*)a4;
    *va = 0;
    double v6 = *a3;
    double v7 = v5 * v5 + v4 * v4 - 0.0;
    if (*a3 >= 0.0)
        v6 = v6;
    else
        v6 = -v6;
    int v8 = *va;
    if (v6 >= fabs(v7))
        v8 = 1;
    *va = v8;
}
