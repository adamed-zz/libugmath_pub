






void h800(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    double v5 = *a1 / *a2;
    double v6 = v5 * v5 * v5;
    double v7 = (v6 - v5 * v5) * *a2;
    double v8 = v5 * v5 * 3.0 - (v6 + v6);
    double v9 = (v5 - v5 * v5) * *a2 + v7;

    *a5 = (1.0 - v8) * *a3 + v8 * *a4 + v9 * a3[3] + v7 * a4[3];
    a5[1] = (1.0 - v8) * a3[1] + v8 * a4[1] + v9 * a3[4] + v7 * a4[4];
    a5[2] = (1.0 - v8) * a3[2] + v8 * a4[2] + v9 * a3[5] + v7 * a4[5];
}
