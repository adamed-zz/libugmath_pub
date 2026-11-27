









void h059(double* a1, double* a2, const double* a3, const double* a4)
{
    double v4 = *a1;
    double v5 = *a2;
    *a1 = *a2 * *a3 + *a1 * *a4;
    *a2 = v5 * *a4 - v4 * *a3;
}
