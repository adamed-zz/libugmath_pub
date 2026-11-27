







void NR_cholesky_solver(double* a, int n, double* const p, double* const b, double* const x)
{
    int i, k;
    double sum;

    for (i = 0; i < n; ++i)
    {
        sum = b[i];
        for (k = i - 1; k >= 0; --k)
            sum -= a[i * n + k] * x[k];
        x[i] = sum / p[i];
    }
    for (i = n - 1; i > 0; --i)
    {
        sum = x[i];
        for (k = i + 1; k < n; ++k)
            sum -= a[k * n + i] * x[k];
        x[i] = sum / p[i];
    }
}
