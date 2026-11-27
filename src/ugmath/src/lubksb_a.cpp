









void lubksb_a(double **a, int n, int *indx, double *b)
{
    int i, ip, j;
    int ii;
    int found = 0;
    double sum;

    for (i = 0; i < n; i++) {
        ip = indx[i];
        sum = b[ip];
        b[ip] = b[i];
        if (found) {
            for (j = ii; j < i; j++)
                sum -= a[i][j] * b[j];
        } else if (sum != 0.0) {
            found = 1;
            ii = i;
        }
        b[i] = sum;
    }
    for (i = n - 1; i >= 0; i--) {
        sum = b[i];
        for (j = i + 1; j < n; j++)
            sum -= a[i][j] * b[j];
        b[i] = sum / a[i][i];
    }
}
