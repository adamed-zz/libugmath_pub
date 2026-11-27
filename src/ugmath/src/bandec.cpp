









#include <math.h>

void bandec(double **a, int n, int m1, int m2, double **al, int *indx, double *d)
{
    int v91 = m1 + m2 + 1;
    int v92 = m1 + m2;

    if (m1 >= 1)
    {
        int v10 = m1;
        int v15 = m2 + 1;
        int v14 = m1 + 1;
        for (int row = 1; row <= m1; ++row)
        {
            double *v22 = a[row - 1];
            if (v14 <= v91)
            {
                for (int k = v14; k <= v91; ++k)
                    v22[k - 1 - v10] = v22[k - 1];
            }
            --v10;
            if (++v15 <= v91)
                for (int z = 0; z < v10 + 1; ++z)
                    v22[v15 - 1 + z] = 0.0;
            --v14;
        }
    }

    *d = 1.0;
    for (int i = 1; i <= n; ++i)
    {
        int v36 = i + m1;
        if (v36 > n) v36 = n;
        if (v36 < m1) v36 = m1;



        double best = a[i - 1][0];
        int bestRow = i - 1;
        for (int r = i; r <= v36; ++r)
        {
            double v = a[r - 1][0];
            if (fabs(v) > fabs(best))
            {
                best = v;
                bestRow = r - 1;
            }
        }
        indx[i - 1] = bestRow + 1;
        if (best == 0.0)
            a[i - 1][0] = 1.0e-20;

        if (bestRow != i - 1)
        {
            *d = -*d;

            double *v55 = a[bestRow];
            double *v56 = a[i - 1];
            for (int k = 0; k < v91; ++k)
            {
                double t = v56[k];
                v56[k] = v55[k];
                v55[k] = t;
            }
        }

        double piv = a[i - 1][0];
        int v37 = v36;
        if (i < v37)
        {
            for (int r = i + 1; r <= v37; ++r)
            {
                double q = a[r - 1][0] / piv;
                al[i - 1][r - i - 1] = q;


                for (int t = 0; t < m1 + m2; ++t)
                    a[r - 1][t] = a[r - 1][t + 1] - q * a[i - 1][t + 1];
                a[r - 1][m1 + m2] = 0.0;
            }
        }
    }
}
