










#include <math.h>

#ifdef UGM_LOCAL_SM
void* SM_alloc(unsigned __int64 size);
void  SM_free(void* p);
#else
__declspec(dllimport) void* SM_alloc(unsigned __int64 size);
__declspec(dllimport) void  SM_free(void* p);
#endif

void NR_ask_max_eigen_val_vec(int n, double** mat, int max_iter, double* x0,
                              double* eigen_val, double* eigen_vec, int* flag)
{
    double* work = (double*)SM_alloc(sizeof(double) * n);
    double* xp   = (double*)SM_alloc(sizeof(double) * n);
    double* x    = (double*)SM_alloc(sizeof(double) * n);
    double* y    = (double*)SM_alloc(sizeof(double) * n);

    *flag = 0;
    for (int i = 0; i < n; i++)
        x[i] = x0[i];

    char converged = 0;
    int iter = 0;
    double maxv;

    if (max_iter > 0)
    {
        for (; iter < max_iter; iter++)
        {
            if (converged)
                break;
            if (n > 0)
            {
                for (int i = 0; i < n; i++)
                {
                    double s = 0.0;
                    for (int j = 0; j < n; j++)
                        s += mat[i][j] * x[j];
                    y[i] = s;
                }
            }
            maxv = y[0];
            for (int i = 1; i < n; i++)
                if (fabs(y[i]) > fabs(maxv))
                    maxv = y[i];
            for (int j = 0; j < n; j++)
                x[j] = y[j] / maxv;
            if (iter > 0)
            {
                double d2 = 0.0;
                double p2 = 0.0;
                for (int j = 0; j < n; j++)
                {
                    double d = x[j] - xp[j];
                    work[j] = d;
                    d2 += d * d;
                    p2 += xp[j] * xp[j];
                }
                if (p2 * 1e-10 >= d2)
                    converged = 1;
            }
            for (int j = 0; j < n; j++)
                xp[j] = x[j];
        }
    }
    if (converged == 1)
    {
        *eigen_val = maxv;
        for (int j = 0; j < n; j++)
            eigen_vec[j] = x[j];
    }
    else
    {
        *flag = 1;
        *eigen_val = maxv;
        for (int j = 0; j < n; j++)
            eigen_vec[j] = x[j];
    }

    if (work)
        SM_free(work);
    if (xp)
        SM_free(xp);
    if (x)
        SM_free(x);
    if (y)
        SM_free(y);
}
