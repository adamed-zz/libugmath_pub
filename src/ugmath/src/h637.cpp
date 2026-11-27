






void h637(const double* a1, const double* a2, double* a3)
{
    a3[0] = a2[0];
    a3[1] = a2[1];
    a3[2] = a2[2];
    a3[3] = a1[1] * a2[1] + a1[0] * a2[0] + a1[2] * a2[2];
}
