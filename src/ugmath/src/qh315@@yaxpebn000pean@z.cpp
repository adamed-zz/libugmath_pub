






extern void vcru3(const double* a1, const double* a2, int* ok, double* out);
extern void h310(const double* a1, const double* a2, const double* a3, double* a4);

void h315(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    double v9[5];
    int v10;
    vcru3(a2, a4, &v10, v9);
    if (v10 == 1)
    {
        double v8 = (*a1 - *a3) * v9[0] + (a1[1] - a3[1]) * v9[1] + (a1[2] - a3[2]) * v9[2];
        if (v8 < 0.0)
            v8 = -v8;
        *a5 = v8;
    }
    else
    {
        h310(a1, a3, a4, a5);
    }
}
