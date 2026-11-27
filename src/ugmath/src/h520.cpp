









#include <math.h>

extern void h014(double* a1, double* a2, double* a3, int* a4, int* a5, int* a6);
extern void h053(const double* a1, const double* a2, double* a3);

void h520(const double* a1, const double* a2, const double* a3, int* a4,
          double* a5, double* a6)
{
    double v7 = *a1;
    double v8 = a1[1];
    double v9 = *a2;
    double v10 = a2[1];
    double v11 = *a2;
    double v21[3];
    v21[0] = v8 * v8 + v7 * v7 - *a3 * *a3;
    v21[1] = v10 * v8 + v11 * v7 + v10 * v8 + v11 * v7;
    v21[2] = v10 * v10 + v9 * v9;
    double r1[2] = {0.0, 0.0};
    double r2[2] = {0.0, 0.0};
    double ang[2] = {0.0, 0.0};
    int v24, v23, v22;
    h014(v21, r1, r2, &v24, &v23, &v22);
    int v12 = v22;
    if (v22 > 1)
    {
        for (int i = 0; i < v22; i++)
        {
            double v16 = r1[i] * v10 + v8;
            double v25 = r1[i] * v9 + v7;
            h053(&v16, &v25, &ang[i]);
        }
        a5[0] = r1[0];
        a5[1] = r1[1];
        a6[0] = ang[0];
        a6[1] = ang[1];
        *a4 = v12;
    }
    else
    {
        *a4 = 0;
    }
}
