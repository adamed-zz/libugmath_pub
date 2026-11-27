








#include <math.h>

extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode0 = 0;

void h434(const double* a1, const double* a2, const double* a3, int* a4)
{
    *a4 = 2;
    double v5y = a2[1] - a1[1];
    double v6y = a3[1] - a1[1];
    double v7 = *a2 - *a1;
    double v8 = a2[2] - a1[2];
    double v9 = *a3 - *a1;
    double v10 = a3[2] - a1[2];
    double cx = v6y * v8 - v10 * v5y;
    double cy = v10 * v7 - v9 * v8;
    double cz = v9 * v5y - v6y * v7;
    double v11 = cx * cx + cy * cy + cz * cz;
    double v12 = sqrt(v11);
    double v16 = v12;
    int v15;
    h805(&v16, &kZero, &kMode0, &v15);
    if (!v15
        || v6y * v5y + v9 * v7 + v10 * v8 < 0.0
        || sqrt(v6y * v6y + v9 * v9 + v10 * v10) > sqrt(v5y * v5y + v7 * v7 + v8 * v8))
    {
        *a4 = 1;
    }
}
