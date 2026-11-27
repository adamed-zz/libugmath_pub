





void h006(double *a1, const double *a2, const double *a3, const int *a4,
          const double *a5, int *a6, int *a7);

void h0005(double *a1, double *a2, double *a3, double *a4, int *a5)
{
    *a5 = 0;
    int v11 = 1;
    int v13;
    double v12 = *a2 + *a3;
    h006(a1, a2, &v12, &v11, a3, &v13, a5);
    *a4 = (double)*a5 * *a3 + *a1;
}
