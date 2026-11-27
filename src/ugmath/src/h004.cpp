








void h004(const double* a1, const double* a2, const double* a3, double* a4)
{
    *a4 = (a3[2] * a2[1] - a3[1] * a2[2]) * *a1
        - (*a2 * a3[2] - *a3 * a2[2]) * a1[1]
        + (*a2 * a3[1] - *a3 * a2[1]) * a1[2];
}
