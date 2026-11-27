






void h704(const double* a1, const double* a2, const double* a3, double* a4, double* a5);

void h706(double* const a1, double* const a2, double* const a3, int* a4)
{
    double v5 = *a2;
    double v6 = a1[1];
    double v7 = a2[1];
    double v8x = a3[0];
    double v8y = a3[1];
    double v10[3];
    double v9[3];
    double v11[3];
    double v12 = 0.0;
    double v13;
    double v14;

    v10[0] = *a1;
    v9[0] = v5;
    v10[1] = v6;
    v9[1] = v7;
    v10[2] = 0.0;
    v9[2] = 0.0;
    v11[2] = v12;
    v11[0] = v8x;
    v11[1] = v8y;


    if (!(v10[0] * v7 - v5 * v6 > 0.0))
    {
        h704(v11, v10, v9, &v13, &v14);
        if (v13 > 0.0 && v14 > 0.0)
        {
            *a4 = 1;
            return;
        }
        *a4 = 0;
        return;
    }
    h704(v11, v10, v9, &v13, &v14);
    if (!(v13 >= 0.0) || !(v14 >= 0.0))
    {
        *a4 = 1;
        return;
    }
    *a4 = 0;
}
