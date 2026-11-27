






int h0917(double a1, const double* a2, int a3, double a4);

int h0917x(double a1, const double* a2, int a3, int a4, double a5)
{
    if (a1 == a2[a3 - a4])
        a1 -= 5.0e-13;
    return h0917(a1, a2, a3, a5);
}
