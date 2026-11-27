








void h0721(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v4 = a2[1];
    double v5 = a1[1];
    *a4 = (*a2 - *a1) * *a3 + *a1;
    a4[1] = (v4 - v5) * *a3 + a1[1];
}
