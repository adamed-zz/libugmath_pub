






extern void h310(const double* a1, const double* a2, const double* a3, double* a4);

void h311(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v6[3];
    v6[0] = *a3 - *a2;
    v6[1] = a3[1] - a2[1];
    v6[2] = a3[2] - a2[2];
    h310(a1, a2, v6, a4);
}
