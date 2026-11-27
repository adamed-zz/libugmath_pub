













#include <math.h>

void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h633(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7)
{
    static const double kZero = 0.0;
    static const int kSelLength = 1;

    double v9 = a4[1];
    double v10 = a4[2];
    double v11 = a4[0];
    double v12 = a3[0] - a1[0];
    double v13 = a3[1] - a1[1];
    double v14 = a3[2] - a1[2];
    double v22 = *a4 * (a2[0] - a1[0]) + v9 * (a2[1] - a1[1]) + v10 * (a2[2] - a1[2]);
    double v23 = v11 * v12 + v9 * v13 + v10 * v14;
    int st;

    h805(&v22, &kZero, &kSelLength, &st);
    if (st == 1)
    {
        *a5 = 3;
    }
    else if (!st)
    {
        double t = v23 / v22;
        double y = (a2[1] - a1[1]) * t + a1[1];
        double z = (a2[2] - a1[2]) * t + a1[2];
        *a7 = v23 / v22;
        a6[0] = t * (a2[0] - a1[0]) + a1[0];
        a6[1] = y;
        a6[2] = z;
        *a5 = 1;
        return;
    }
    h805(&v23, &kZero, &kSelLength, &st);
    if (st == 1)
    {
        *a5 = 2;
        a6[0] = a1[0];
        a6[1] = a1[1];
        a6[2] = a1[2];
        *a7 = 0.0;
    }
}
