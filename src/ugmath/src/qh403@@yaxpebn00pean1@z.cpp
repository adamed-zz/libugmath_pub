





extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kZero403 = 0.0;
static const int kMode403 = 2;

void h403(const double* a1, const double* a2, const double* a3, double* a4, double* a5)
{
    double v6 = *a3 - *a2;
    double v9 = a3[1] - a2[1];
    double v14 = v9 * v9 + v6 * v6;
    int v13;
    h805(&v14, &kZero403, &kMode403, &v13);
    if (v13 == 1)
    {
        *a4 = *a2;
        a4[1] = a2[1];
        *a5 = 0.0;
    }
    else
    {
        double* v11 = a5;
        double v12 = ((a1[1] - a2[1]) * v9 + (*a1 - *a2) * v6) / v14;
        *a5 = v12;
        *a4 = (*a3 - *a2) * v12 + *a2;
        a4[1] = (a3[1] - a2[1]) * *v11 + a2[1];
    }
}
