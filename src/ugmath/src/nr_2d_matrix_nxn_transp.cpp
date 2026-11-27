










void NR_2d_matrix_nxn_transp(double **a, int n)
{
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            double t = a[j][i];
            a[j][i] = a[i][j];
            a[i][j] = t;
        }
}
