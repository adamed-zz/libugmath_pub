





#include "common.h"

extern "C" void __fastcall sub_1800032B0(double *a1, double a2, double *a3, double *a4,
                                         __int64 a5, int *a6, double *a7, double *a8)
{
    double v26 = a3[1];
    double v29 = a3[2];
    double v30 = a4[1];
    double v31 = a4[2];
    double v32 = a4[0];
    double v13 = a3[0];
    double v27 = a3[0];
    double v28 = 0.0;
    double roots[2] = { 0.0, 0.0 };

    *a6 = 0;

    double m0 = a1[0] + a1[0];
    double m1 = a1[1] + a1[1];
    double v11 = a1[0] * a1[0];
    double v9 = -(a1[1] * a1[1] + v11 - a2 * a2);

    double v12 = cos(*(double *)&a5 * kDeg2Rad);
    double v15 = a2 * a2 * v12 * v12;
    double v16 = m0 * m0;
    double v10 = m0 * -2.0;
    double v17 = v10 * -1.0;
    double v18 = v10 * m1;
    double v19 = v15 * 4.0 - v16;
    v10 = v10 * v9;
    double v20 = m1 * m1;
    double v21 = m1 * -2.0;
    double v22 = v15 * 4.0 - v20;
    double v23 = (v15 + v15 - v9 * 1.0) * -2.0;

    double A = v22 * v30 * v30 + v19 * v32 * v32 - v31 * 1.0 * v31
             + v18 * v32 * v30 + v17 * v32 * v31 + v21 * -1.0 * v30 * v31;




    double Bt = (v32 * v29 + v31 * v13) * v17
              + (v32 * v26 + v30 * v13) * v18
              + (v30 * v29 + v31 * v26) * (v21 * -1.0);
    double Bu = (v22 + v22) * v26 * v30
              + (v19 + v19) * v13 * v32
              - v29 * 2.0 * v31;
    double Bs = (v21 * v9 * v30
              + v10 * v32)
              + v23 * v31;
    double B = (Bt + Bu) + Bs;
    double C = v22 * v26 * v26
             + v19 * v13 * v13
             - v29 * 1.0 * v29
             + v18 * v13 * v26
             + v17 * v13 * v29
             + v21 * -1.0 * v26 * v29
             + v10 * v13
             + v21 * v9 * v26
             + v23 * v29
             + -v9 * v9;

    ARC_SPLINE_solve_quadratic_eqt(A, B, C, 1, roots, a6);
    v27 = roots[0];
    v28 = roots[1];
    if (*a6 > 0)
    {
        double v24 = v27;
        *a7 = v27 * v32 + v13;
        a7[1] = v24 * v30 + v26;
        a7[2] = v24 * v31 + v29;
        if (*a6 > 1)
        {
            double v25 = v28;
            *a8 = v28 * v32 + v13;
            a8[1] = v25 * v30 + v26;
            a8[2] = v25 * v31 + v29;
        }
    }
    else
        *a6 = 0;
}
