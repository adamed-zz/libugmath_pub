










void h0711(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v4 = (*a3 - *a1) / (*a2 - *a1);
    double v5 = v4 * 4.0 - 3.0;
    a4[1] = 4.0 - v4 * 8.0;
    *a4 = v5;
    a4[2] = v5 + 2.0;
}
