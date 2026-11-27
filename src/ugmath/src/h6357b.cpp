


















#include <math.h>

void vunt3(const double* a1, int* a2, double* a3);
void h633(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7);

void h6357b(const double* a1, const double* a2, const double* a3, const double* a4,
            int* a5, int* a6, double* a7)
{
    double v18[3];
    double v20[3];
    double v23[3];
    int st;
    double t;
    double* v11 = a7;

    *a5 = 0;
    v20[0] = a3[0] + a4[0];
    v20[1] = a3[1] + a4[1];
    v20[2] = a3[2] + a4[2];
    vunt3(a4, a6, v18);
    h633(a1, a2, v20, v18, &st, v23, &t);
    if (st == 1)
    {
        v11[0] = t;
        v11[1] = t;
        if (!*a6)
        {
            *a5 = 2;
            return;
        }
        v20[0] = a3[0] - a4[0];
        v20[1] = a3[1] - a4[1];
        v20[2] = a3[2] - a4[2];
        v18[0] = v18[0] * -1.0;
        v18[1] = v18[1] * -1.0;
        v18[2] = v18[2] * -1.0;
        h633(a1, a2, v20, v18, &st, v23, &t);
        if (st == 1)
        {
            if (v11[0] > t)
                v11[0] = t;
            else
                v11[1] = t;
            *a5 = 2;
        }
        else
        {
            *a5 = 1;
        }
        return;
    }
    if (st == 2)
    {
        *a5 = 1;
        return;
    }
    {
        double dot1 = (v20[1] - a1[1]) * v18[1]
                    + (v20[0] - a1[0]) * v18[0]
                    + (v20[2] - a1[2]) * v18[2];
        if (0.0 > dot1)
            return;
        double sx = (a3[0] - a4[0]) - a1[0];
        double sy = (a3[1] - a4[1]) - a1[1];
        double sz = (a3[2] - a4[2]) - a1[2];
        double dot2 = sx * (v18[0] * -1.0)
                    - sy * (v18[1] * 1.0)
                    - sz * (v18[2] * 1.0);
        if (0.0 > dot2)
            return;
        *a5 = 1;
    }
}
