









int __declspec(noinline) SOLVE_solve_3equations(double (*const A)[3],
                                                double* const b,
                                                double* const x);

int BCDF_CALC_quadratic_apprx(double* const a1, double* const a2,
                              double* const a3, double* const a4,
                              int a5, double a6, int a7, double* a8)
{
    double A[3][3];
    double b[3];
    double x[3];
    double c0[3], c1[3], c2[3];

    if (a5 == 2)
    {

        A[0][0] = a4[0] * a4[0];
        A[0][1] = a4[0];
        A[0][2] = 1.0;
        A[1][0] = a4[1] + a4[1];
        A[1][1] = 1.0;
        A[1][2] = 0.0;
    }
    else
    {

        A[0][0] = a4[0] * a4[0];
        A[0][1] = a4[0];
        A[0][2] = 1.0;
        A[1][0] = a4[1] * a4[1];
        A[1][1] = a4[1];
        A[1][2] = 1.0;
    }
    if (a5 == 1)
    {

        A[2][0] = a4[2] + a4[2];
        A[2][1] = 1.0;
        A[2][2] = 0.0;
    }
    else
    {

        A[2][0] = a4[2] * a4[2];
        A[2][1] = a4[2];
        A[2][2] = 1.0;
    }

    int k;
    for (k = 0; k < 3; ++k)
    {
        b[0] = a1[k];
        b[1] = a2[k];
        b[2] = a3[k];
        const int rc = SOLVE_solve_3equations(A, b, x);
        if (rc != 0)
            return rc;
        c0[k] = x[0];
        c1[k] = x[1];
        c2[k] = x[2];
    }

    const double t = a6;
    if (a7 >= 0)
    {
        for (k = 0; k < 3; ++k)
            a8[k] = (c0[k] * t + c1[k]) * t + c2[k];
    }
    if (a7 >= 1)
    {
        for (k = 0; k < 3; ++k)
            a8[k + 3] = (c0[k] + c0[k]) * t + c1[k];
    }
    if (a7 >= 2)
    {
        for (k = 0; k < 3; ++k)
            a8[k + 6] = c0[k] + c0[k];
    }
    return 0;
}




