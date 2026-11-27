






extern void h301(const double* a, const double* b, double* out);
extern void h806(const double* a, const double* b, double* tol, int* out);

static const double kZero307 = 0.0;

void h307(const double* a1, const double* a2, const double* a3, int* a4)
{
    double v6;
    h301(a1, a2, &v6);
    h806(&v6, &kZero307, (double*)a3, a4);
}
