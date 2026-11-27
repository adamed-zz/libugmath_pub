





void h961(const double* a1, const double* a2, double* a3)
{
    double v = a2[12];
    if (!(v >= 0.0))
        v = -v;
    *a3 = v * a1[0];
}
