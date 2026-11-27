








#include <math.h>

void h641(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, int* a6, int* a7, double* a8);

void h651(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, int* a6, double* a7)
{
    double* v7 = a7;

    h641(a1, a2, a3, a4, a5, (int*)&a7, a6, v7);
    double v9 = v7[1];
    v7[4] = v9;
    if (*a6 != 1 && *a6 != 4)
    {
        v7[1] = cos(*v7) * *a5 + *a4;
        v7[2] = sin(*v7) * *a5 + a4[1];
        v7[3] = a4[2];
        if (*a6 != 2)
        {
            v7[5] = cos(v9) * *a5 + *a4;
            v7[6] = sin(v9) * *a5 + a4[1];
            v7[7] = a4[2];
        }
    }
}
