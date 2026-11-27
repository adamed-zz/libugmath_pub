






int eqz(const double* a, const double* b, const int* mode);
extern const double g_zero;
extern const int g_mode;

void h091(const double* a1, const double* a2, int* a3)
{
    *a3 = 0;
    double v4 = a1[1] * a2[1];
    double v5 = a1[2] * a2[2];
    double s = v4 + *a1 * *a2 + v5;
    double v6 = s * s;
    if (eqz(&v6, &g_zero, &g_mode))
        *a3 = 1;
}
