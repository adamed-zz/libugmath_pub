


#include <cmath>

void *SM_alloc(long long n);
void SM_free(void *p);

extern "C" void sub_1800AFB80(double **a1, double *a2, double **a3, int a4, int a5,
                   int *a6, double *a7, double *a8, double a9)
{
    double v12 = 0.0;
    int v9 = 0;
    if (a5 >= 4)
    {
        int chunks = ((a5 - 4) >> 2) + 1;
        v9 = 4 * chunks;
        for (int c = 0; c < chunks; c++)
        {
            double v16 = a2[4 * c + 1];
            double v17 = fmax(a2[4 * c + 0], v12);
            double v18 = a2[4 * c + 2];
            double v19 = a2[4 * c + 3];
            v12 = fmax(v19, fmax(v18, fmax(v16, v17)));
        }
    }
    for (int i = v9; i < a5; i++)
        v12 = fmax(a2[i], v12);
    double v21 = v12 * a9;
    double *v22 = (double *)SM_alloc(8LL * a5);
    *a6 = a5;
    for (int j = 0; j < a5; j++)
    {
        double v28 = 0.0;
        if (!(v21 >= fabs(a2[j])))
        {
            for (int i = 0; i < a4; i++)
                v28 = v28 + a1[i][j] * a7[i];
            v28 = v28 / a2[j];
        }
        else
        {
            --*a6;
        }
        v22[j] = v28;
    }
    for (int i = 0; i < a5; i++)
    {
        double v43 = 0.0;
        for (int j = 0; j < a5; j++)
            v43 = v43 + a3[i][j] * v22[j];
        a8[i] = v43;
    }
    SM_free(v22);
}
