









#include <math.h>

void NR_cholesky_decomp(int n, double* a, double* const p, int* status)
{
    *status = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double sum = a[i * n + j];
            for (int k = i - 1; k >= 0; k--)
                sum -= a[i * n + k] * a[j * n + k];
            if (i == j)
            {
                if (sum < 1.0e-10)
                {
                    *status = 1;
                    return;
                }
                p[i] = sqrt(sum);
            }
            else
            {
                a[j * n + i] = sum / p[i];
            }
        }
    }
}
