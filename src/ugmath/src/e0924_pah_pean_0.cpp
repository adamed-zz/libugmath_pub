










#include <cmath>

void e0924(int* a1, double* a2, int* a3)
{
    double v3 = *a2;
    *a3 = 1;
    int v4 = 1;
    int v5 = 1;
    if (*a1 <= 1)
        return;
    double* v6 = a2 + 1;
    do
    {
        int v8 = fabs(*v6 - v3) < 1.0e-10;
        if (!v8)
        {
            v3 = *v6;
            int v9 = fabs(*(v6 - 1) - 0.0) < 1.0e-10;
            int v10 = fabs(*(v6 - 1) - 1.0) < 1.0e-10;
            if (!v9 && !v10 && v4 > *a3)
                *a3 = v4;
            v4 = 1;
        }
        else
        {
            ++v4;
        }
        ++v5;
        ++v6;
    } while (v5 < *a1);
}
