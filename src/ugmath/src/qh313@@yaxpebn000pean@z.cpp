





extern void h315(const double* a1, const double* a2, const double* a3, const double* a4, double* a5);

void h313(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    double v11[3], v10[3];
    v11[0] = *a2 - *a1;
    v11[1] = a2[1] - a1[1];
    v11[2] = a2[2] - a1[2];
    v10[0] = *a4 - *a3;
    v10[1] = a4[1] - a3[1];
    v10[2] = a4[2] - a3[2];
    h315(a1, v11, a3, v10, a5);
}
