











void NR_cholesky_inverse(int n, double* const d, double* a)
{
    if (n <= 0)
        return;
    int i = 0;
    do
    {
        a[i * n + i] = 1.0 / d[i];
        int j = i + 1;
        while (j < n)
        {
            double sum = 0.0;
            int k = i;
            while (k < j)
            {
                sum -= a[k * n + i] * a[j * n + k];
                ++k;
            }
            a[j * n + i] = sum / d[j];
            ++j;
        }
        ++i;
    } while (i < n);
}
