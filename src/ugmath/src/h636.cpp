













void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h636(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    static const double kZero = 0.0;
    static const int kSelNumber = 0;

    double v13;
    double v14;
    int st;

    a5[0] = a1[0];
    a5[1] = a1[1];
    a5[2] = a1[2];
    double v9 = a3[1] * a2[1];
    double v10 = a3[0] * a2[0];
    double v11 = a3[2] * a2[2];
    v14 = a3[3] - (a3[0] * a1[0] + a3[1] * a1[1] + a3[2] * a1[2]);
    v13 = v9 + v10 + v11;
    h805(&v13, &kZero, &kSelNumber, &st);
    if (!st)
    {
        double t = v14 / v13;
        *a4 = 2;
        a5[0] = t * a2[0] + a1[0];
        a5[1] = t * a2[1] + a1[1];
        a5[2] = t * a2[2] + a1[2];
    }
    else
    {
        *a4 = 1;
        h805(&v14, &kZero, &kSelNumber, &st);
        if (st == 1)
            *a4 = 3;
    }
}
