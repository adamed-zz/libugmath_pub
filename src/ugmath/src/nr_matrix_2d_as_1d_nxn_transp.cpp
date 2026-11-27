










void NR_matrix_2d_as_1d_nxn_transp(double *a, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            double t = a[j * n + i];
            a[j * n + i] = a[i * n + j];
            a[i * n + j] = t;
        }
}
