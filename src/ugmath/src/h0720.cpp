









void h0720(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    double v2 = *a1 * *a2;
    double v0 = a1[1] * *a3;
    double v1 = a1[2] * *a4;
    *a5 = v2 + v0 + v1;
    double w2 = a2[1] * *a1;
    double w0 = a3[1] * a1[1];
    double w1 = a4[1] * a1[2];
    a5[1] = w2 + w0 + w1;
}
