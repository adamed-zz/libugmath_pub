






#include <cstring>
#include <cmath>


typedef void (__cdecl *NR_qsimp_fn)(void *ctx, double *x, double * const f, int *flag);


extern "C" void sub_1800A1AB0(void *ctx, NR_qsimp_fn fn, int n, double a, double b,
                               int j, double *s);



static double __declspec(noinline) sub_1800A2130(const double *x, const double *y, int n)
{
    double m = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double t = fabs(x[i] - y[i]);
        m = (m > t) ? m : t;
    }
    return m;
}


static __forceinline double NR_maxabs(const double *v, int last)
{
    double t[8];
    for (int i = 0; i < 4; ++i)
        t[i] = fabs(v[i]);
    double m = t[0];
    for (int i = 1; i <= last; ++i)
        m = (m > t[i]) ? m : t[i];
    return m;
}

void __cdecl NR_qsimp(void *ctx, NR_qsimp_fn fn, int n, double a, double b,
                      double eps, int jmax, double * const out, int *status)
{
    double hi[8];
    double st[8];
    double s[8];
    double s2[8];

    const double half = eps * 0.5;

    *status = 0;
    if (n > 8)
    {
        *status = 2;
        return;
    }
    if (n > 0)
    {
        for (int i = 0; i < n; ++i)
            hi[i] = -1e30;
        for (int i = 0; i < n; ++i)
            st[i] = -1e30;
    }
    if (jmax < 1)
    {
        *status = 1;
        return;
    }
    const int last = n - 1;
    for (int j = 1; j <= jmax; ++j)
    {
        sub_1800A1AB0(ctx, fn, n, a, b, j, s);
        for (int i = 0; i < n; ++i)
            s2[i] = (4.0 * s[i] - st[i]) / 3.0;
        double tol;
        if (NR_maxabs(hi, last) * eps > half)
            tol = NR_maxabs(hi, last) * eps;
        else
            tol = half;
        double err = sub_1800A2130(s2, hi, n);
        if (tol > err)
        {
            if (n > 0)
                memcpy(out, s2, n * sizeof(double));
            return;
        }
        if (n > 0)
        {
            memcpy(st, s, n * sizeof(double));
            memcpy(hi, s2, n * sizeof(double));
        }
    }
    *status = 1;
}
