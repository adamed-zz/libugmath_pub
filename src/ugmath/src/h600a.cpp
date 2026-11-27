









#include <math.h>

extern int eqz(const double* a1, const double* a2, const int* a3);

static const double kZero = 0.0;
static const int kMode2 = 2;
static const int kMode3 = 3;

void h600a(const double* a1, const double* a2, const double* a3, const double* a4,
           int* a5, double* a6)
{
    *a5 = 1;
    double v10 = *a2 - *a1;
    double v11 = a2[1] - a1[1];
    double v19 = v10 * v10 + v11 * v11;
    if (!eqz(&v19, &kZero, &kMode2))
    {
        double v12 = *a4 - *a3;
        double v13 = a4[1] - a3[1];
        double len2b = v13 * v13 + v12 * v12;
        if (!eqz(&len2b, &kZero, &kMode2))
        {
            double v14 = a3[1] - a1[1];
            double v15 = *a3 - *a1;
            double v16 = v10 * v13 - v11 * v12;
            double v20 = v16 * v16 / (len2b * v19);
            if (eqz(&v20, &kZero, &kMode3))
            {
                double t = (v14 * v10 - v15 * v11) * (v14 * v10 - v15 * v11) / v19;
                if (eqz(&t, &kZero, &kMode2))
                    *a5 = 4;
            }
            else
            {
                double* v17 = a6;
                double v18 = (v15 * v13 - v14 * v12) / v16;
                v17[0] = v10 * v18 + *a1;
                v17[1] = v11 * v18 + a1[1];
                *a5 = 2;
            }
        }
    }
}
