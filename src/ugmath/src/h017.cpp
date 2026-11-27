








void h017(double* a1, double* a2, double* a3)
{
    a3[1] = *a1 * a2[1] + a1[1] * *a2;
    *a3 = *a1 * *a2 - a1[1] * a2[1];
}
