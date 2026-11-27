





void h815(const double* a1, const double* a2, const double* a3, double* a4);
void h116(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, double* a6);

void h810(const double* a1, const double* a2, const double* a3, const double* a4,
          const double* a5, const double* a6, const double* a7, double* a8)
{
    double v10[4];

    h815(a1, a4, a7, v10);
    h116(v10, a2, a3, a5, a6, a8);
}
