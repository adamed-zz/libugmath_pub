








#include <cmath>

#define MAXV(a, b) ((a) > (b) ? (a) : (b))

void *SM_alloc(long long n);
void SM_free(void *p);

extern "C" void sub_1800AFE80(double **a1, double *a2, double **a3, int a4, int a5,
                   int *a6, int a7, double **a8, double **a9, double a10)
{
    int v24;
    double v20;
    double v12 = 0.0;
    int v10 = 0;
    if (a5 >= 4)
    {
        int chunks = ((a5 - 4) >> 2) + 1;
        v10 = 4 * chunks;
        for (int c = 0; c < chunks; c++)
        {
            for (int k = 0; k < 4; ++k)
                v12 = MAXV(a2[4 * c + k], v12);
        }
    }
    for (int i = v10; i < a5; i++)
        v12 = MAXV(a2[i], v12);
    v20 = v12 * a10;
    double *v22 = (double *)SM_alloc(8LL * a5);
    *a6 = a5;
    if (a7 > 0)
    {
        v24 = 0;
        do
        {
            for (int j = 0; j < a5; j++)
            {
                double v28 = 0.0;
                if (v20 >= fabs(a2[j]))
                {
                    if (!v24)
                        --*a6;
                }
                else
                {
                    for (int i = 0; i < a4; i++)
                        v28 = v28 + a1[i][j] * a8[i][v24];
                    v28 = v28 / a2[j];
                }
                v22[j] = v28;
            }
            for (int i = 0; i < a5; i++)
            {
                double v45 = 0.0;
                for (int j = 0; j < a5; j++)
                    v45 = v45 + a3[i][j] * v22[j];
                a9[i][v24] = v45;
            }
            ++v24;
        } while (v24 < a7);
    }
    SM_free(v22);
}
