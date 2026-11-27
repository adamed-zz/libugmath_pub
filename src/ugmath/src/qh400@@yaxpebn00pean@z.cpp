






extern void h401(const double* a1, const double* a2, const double* a3, double* a4);

void h400(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v5[2];
    v5[0] = *a2 - *a1;
    v5[1] = a2[1] - a1[1];
    h401(a1, v5, a3, a4);
}
