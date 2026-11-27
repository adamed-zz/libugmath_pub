








void banbks(double **a, int n, int m1, int m2, double **al, int *indx, double *b)
{
    int mm = m1;

    for (int i = 1; i <= n; ++i)
    {
        int v15 = indx[i - 1];
        if (v15 != i)
        {
            double t = b[i - 1];
            b[i - 1] = b[v15 - 1];
            b[v15 - 1] = t;
        }
        mm = (mm < n) ? mm + 1 : mm;
        for (int k = i + 1; k <= mm; ++k)
            b[k - 1] = b[k - 1] - al[i - 1][k - i - 1] * b[i - 1];
    }

    int lim = 1;
    int cap = m1 + m2 + 1;
    for (int i = n; i >= 1; --i)
    {
        double s = b[i - 1];
        for (int k = 2; k <= lim; ++k)
            s = s - a[i - 1][k - 1] * b[i + k - 2];
        b[i - 1] = s / a[i - 1][0];
        lim = (lim < cap) ? lim + 1 : lim;
    }
}
