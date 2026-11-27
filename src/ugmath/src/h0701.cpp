










extern void h0711(const double* a1, const double* a2, const double* a3, double* a4);
extern void h0720(const double* a1, const double* a2, const double* a3, const double* a4,
                  double* a5);

void h0701(const double* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, double* a7)
{
    double v9[3];
    h0711(a1, a4, a6, v9);
    h0720(v9, a2, a3, a5, a7);
}
