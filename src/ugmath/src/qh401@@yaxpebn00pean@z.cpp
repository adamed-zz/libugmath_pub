







extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kZero401 = 0.0;
static const int kMode401 = 2;

void h401(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v6 = a3[1] - a1[1];
    double v8 = *a3 - *a1;
    double v11 = *a2 * *a2 + a2[1] * a2[1];
    int v10;
    h805(&v11, &kZero401, &kMode401, &v10);
    if (v10 == 0)
    {
        double t = v6 * a2[1];
        t = t + *a2 * v8;
        double v9 = t / v11;
        *a4 = *a2 * v9 + *a1;
        a4[1] = v9 * a2[1] + a1[1];
    }
    else
    {
        *a4 = *a1;
        a4[1] = a1[1];
    }
}
