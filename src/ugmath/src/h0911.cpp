






void h0911(int n, const double* a2, double* a3)
{
    const double x = a2[0];
    const double d = a2[1] - x;
    for (int i = 0; i < n; ++i)
        a3[i] = (a3[i] - x) / d;
}
