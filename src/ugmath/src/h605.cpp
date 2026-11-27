










#include <math.h>

extern int eqz(const double* a1, const double* a2, const int* a3);

static const double kZero = 0.0;
static const int kMode2 = 2;
static const int kMode1 = 1;

void h605(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7)
{
    *a5 = 1;
    double v11 = *a2 - *a1;
    double v12 = a2[1] - a1[1];
    double v13 = *a3 - *a1;
    double v14 = a3[1] - a1[1];
    double len2 = v12 * v12 + v11 * v11;
    if (eqz(&len2, &kZero, &kMode2))
    {
        *a5 = 1;
        return;
    }
    double v15 = v12 * v14;
    double v16 = (v15 + v11 * v13) / len2;
    double v17 = v16 * v12 + a1[1];
    double v18 = v16 * v11 + *a1;
    double dx = *a3 - v18;
    double dy = a3[1] - v17;
    double v19 = dx * dx + dy * dy;
    double v20 = sqrt(v19);
    double v31 = v20;
    if (!eqz(&v31, a4, &kMode1))
    {
        double v21 = v31 - *a4;
        if (v21 < 0.0)
        {
            *a5 = 3;
            double v22 = *a4 * *a4 - v19;
            double v23 = sqrt(v22);
            double v24 = sqrt(len2);
            double v26 = v11 / v24 * v23;
            double v27 = v12 / v24 * v23;
            double v28 = v26 + v18;
            v18 = v18 - v26;
            double v29 = v27 + v17;
            v17 = v17 - v27;
            a6[0] = v28;
            a6[1] = v29;
            a7[0] = v18;
            a7[1] = v17;
            return;
        }
        if (v21 != 0.0)
            return;
    }
    *a5 = 2;
    a6[0] = v18;
    a6[1] = v17;
}
