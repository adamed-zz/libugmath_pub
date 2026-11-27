





void h649y(const double* a1, const double* a2, double* a3)
{
    *a3 = 0.0;
    if (*a1 > 0.0)
        *a3 = *a1;
    if (*a2 < 0.0)
        *a3 = *a2;
}
