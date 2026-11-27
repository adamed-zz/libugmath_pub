






extern void h300(const double* a, const double* b, double* out);
extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kZero302 = 0.0;
static const int kMode302 = 2;

void h302(const double* a1, const double* a2, int* a3)
{
    double v5;
    int v4;
    *a3 = 0;
    h300(a1, a2, &v5);
    h805(&v5, &kZero302, &kMode302, &v4);
    if (v4 == 1)
        *a3 = 1;
}
