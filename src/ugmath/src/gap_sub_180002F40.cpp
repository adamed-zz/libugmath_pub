





#include "common.h"

extern "C" void __fastcall sub_180002F40(double *a1, double *a2, double *a3, double a4,
                                         double a5, double *a6, int *a7, double *a8,
                                         int *a9, int *a10, int *a11, int *a12)
{
    const double kPi = 3.141592653589793;
    double v40[2] = { 0.0, 0.0 };
    double scratch = 0.0;
    const double signs[2] = { 1.0, -1.0 };
    int v19 = -1;

    *a7 = 0;
    a8[0] = 0.0;
    a8[1] = 0.0;
    a9[0] = 1;
    a9[1] = -1;
    *a10 = 1;
    *a11 = 1;
    *a12 = 0;

    double v22 = *a6;
    ARC_SPLINE_ask_dist_pt_to_line_2d((Point2 const *)a3, (Point2 const *)a1,
                                      (Vector2 const *)a2, v22,
                                      (Point2 *)v40, &scratch, a11);

    double v23 = a3[0] - a1[0];
    double v24 = a3[1] - a1[1];
    double v25 = *a6 * *a6;
    double v26 = v23 * v23 + v24 * v24;
    double v27 = v26 - a4 * a4;

    if (!(v25 >= fabs(v27)))
    {
        if (!(a4 * a4 > v26))
            v19 = 1;
        int v28 = 0;
        *a10 = v19;
        int v29 = 0;
        double v31 = a2[0];
        double v32 = -a2[1];
        while (!v28)
        {
            double v34 = signs[v29];
            double v35 = (v31 * v24 + v32 * v23) * v34 + (v31 * v24 + v32 * v23) * v34;
            if (!*a11)
                v35 = 0.0;
            for (int i = 0; i < 2; ++i)
            {
                if (v28)
                    break;
                double v37 = i ? (kPi - a5 * kDeg2Rad) : (a5 * kDeg2Rad);
                double v38 = cos(v37) * -a4 + v35;
                if (fabs(v38 - 0.0) <= 1.0e-10)
                {
                    *a12 = 1;
                    *a7 = 0;
                    return;
                }
                if (v27 / v38 > 1.0e-10)
                {
                    int v39 = *a7;
                    *a7 = v39 + 1;
                    a8[v39] = v27 / v38;
                    a9[*a7 - 1] = (int)v34;
                    if (*a7 == 2)
                        v28 = 1;
                }
            }
            if (++v29 >= 2)
                return;
        }
    }
    else
        *a10 = 0;
}
