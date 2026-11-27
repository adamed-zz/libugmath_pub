





void h100(const double* a1, const double* a2, double* a3);

void h652(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    double v8[3];

    a5[0] = 0.0;
    a5[1] = 6.283185307179586;
    h100(a1, a2, v8);
    a5[2] = a3[0];
    a5[3] = a3[1];
    a5[4] = v8[2];
    a5[5] = a4[0];
}
