







extern void h0908(const int* a1, const double* knots, const double* ctrl, const double* t,
                  double* pt, double* der);
extern void h0900(const int* a1, const double* knots, const double* ctrl, const double* t,
                  double* pt);

void h4301(const int* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, double* a6, double* a7, double* a8)
{
    int idx1 = a1[0];
    int idx2 = a1[1];
    double u = a5[0];
    double v = a5[1];
    double scratch[108];
    double pts[400];
    double ders[400];

    for (int i = 0; i <= idx2; ++i)
    {
        const double* row = a4 + (long long)i * 100;
        int cnt = 4 * (idx1 + 1);
        for (int k = 0; k < cnt; ++k)
            scratch[k] = row[k];
        h0908(&idx1, a2, scratch, &u, pts + 4 * i, ders + 4 * i);
    }
    h0908(&idx2, a3, pts, &v, a6, a8);
    h0900(&idx2, a3, ders, &v, a7);
}
