













#include <math.h>

struct CURVE_PTS
{
    double param;
    double x;
    double y;
    double z;
};

void em0156c(const double* a1, int a2, CURVE_PTS* a3, double* a4)
{
    int v4 = a2 - 1;
    int v5 = 0;
    double v6 = 0.0;
    double v7 = 0.0;
    if (v4 > 0)
    {
        double v8 = *a1;
        double* v9 = (double*)((char*)a3 + 56);
        do
        {
            double v10 = *(v9 - 4);
            double v11 = *(v9 - 6);
            double v12 = *(v9 - 5);
            double v13 = *(v9 - 2) - v11;
            double v14 = *(v9 - 1) - v12;
            double v15 = *v9 - v10;
            double v16 = v14 * v14 + v13 * v13 + v15 * v15;
            double v17;
            if (v16 < 1.0e-20)
                v17 = 0.0;
            else
                v17 = (v13 * (v8 - v11) + v14 * (a1[1] - v12) + v15 * (a1[2] - v10)) / v16;
            double v18;
            double v19;
            double v20;
            if (fabs(v17 - 0.0) <= 1.0e-10 || v17 < 0.0)
            {
                v17 = 0.0;
                v18 = *(v9 - 6);
                v19 = *(v9 - 5);
                v20 = *(v9 - 4);
            }
            else if (fabs(v17 - 1.0) <= 1.0e-10 || v17 > 1.0)
            {
                v18 = *(v9 - 2);
                v17 = 1.0;
                v19 = *(v9 - 1);
                v20 = *v9;
            }
            else
            {
                v18 = v13 * v17 + v11;
                v19 = v14 * v17 + v12;
                v20 = v15 * v17 + v10;
            }
            v8 = *a1;
            double v21 =
                (v19 - a1[1]) * (v19 - a1[1]) + (v18 - v8) * (v18 - v8) + (v20 - a1[2]) * (v20 - a1[2]);
            if (!v5 || v7 > v21)
            {
                v7 = v21;
                v6 = (*(v9 - 3) - *(v9 - 7)) * v17 + *(v9 - 7);
            }
            v9 += 4;
            ++v5;
        } while (v5 < v4);
    }
    *a4 = v6;
}
