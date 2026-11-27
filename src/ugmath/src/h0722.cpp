













extern void h805(const double* a1, const double* a2, const int* a3, int* a4);

static const double kZero = 0.0;
static const int kMode = 0;

void h0722(const double* a1, const double* a2, const double* a3, const double* a4, int* a5,
           double* a6)
{
    int* v6 = a5;
    int res;
    *a5 = 1;
    double v10 = *a3 - *a1;
    double v11 = a3[1] - a1[1];
    double t1 = *a4 * a2[1];
    double t2 = *a2 * a4[1];
    double v14 = t1 - t2;
    h805(&v14, &kZero, &kMode, &res);
    if (res != 1) {
        double v13 = (v11 * *a4 - v10 * a4[1]) / v14;
        *a6 = v13 * *a2 + *a1;
        a6[1] = v13 * a2[1] + a1[1];
        *v6 = 2;
    }
}
