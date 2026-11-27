






#include <math.h>

int GetAlgorithmVersion();

void h750(const double* a1, int* a2)
{
    double v4 = *a1 * *a1 + a1[1] * a1[1] + a1[2] * a1[2];
    double v5 = sqrt(v4);
    double v6 = a1[3] * a1[3] + a1[4] * a1[4] + a1[5] * a1[5];
    double v7 = sqrt(v6);
    double v8 = a1[6] * a1[6] + a1[7] * a1[7] + a1[8] * a1[8];
    double v9 = sqrt(v8);
    if (fabs(v7 - v9) + fabs(v5 - v7) > v5 * 0.000000001)
    {
        *a2 = 0;
        return;
    }
    double v10;
    double v12;
    double v13;
    if (GetAlgorithmVersion() < 24060)
    {
        v10 = a1[4] * a1[1] + *a1 * a1[3] + a1[5] * a1[2];
        v13 = a1[6] * *a1 + a1[7] * a1[1] + a1[8] * a1[2];
        v12 = a1[4] * a1[7] + a1[6] * a1[3] + a1[5] * a1[8];
    }
    else
    {
        v10 = (*a1 * a1[3] + a1[1] * a1[4] + a1[2] * a1[5]) / (v5 * v7);
        double v11 = a1[7];
        v12 = (a1[6] * a1[3] + v11 * a1[4] + a1[8] * a1[5]) / (v9 * v5);
        v13 = (a1[6] * *a1 + v11 * a1[1] + a1[8] * a1[2]) / (v9 * v7);
    }
    double v14 = sqrt(v10 * v10 + v13 * v13 + v12 * v12);
    if (v14 > 0.000000001)
    {
        *a2 = 0;
        return;
    }
    *a2 = 1;
}
