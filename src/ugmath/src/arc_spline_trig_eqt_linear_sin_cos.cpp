


















#include <math.h>

void __cdecl ARC_SPLINE_solve_quadratic_eqt(double a, double b, double c, int mode,
                                            double* const roots, int* nroots);

void __cdecl ARC_SPLINE_trig_eqt_linear_sin_cos(double a1, double a2, double a3,
                                                char a4, int a5, double a6,
                                                int* a7, double* const a8,
                                                double* const a9)
{
    double roots[2];
    int nq;
    double rt[2];
    double ang[2];
    rt[0] = rt[1] = 1.0e30;
    ang[0] = ang[1] = 1.0e30;
    const double PI = 3.141592653589793;

    double R = sqrt(a1 * a1 + a2 * a2 + a3 * a3);
    if (R <= 1.0e-12)
    {
        *a7 = -3;
        return;
    }

    ARC_SPLINE_solve_quadratic_eqt(a2 / R - a3 / R, -(a1 / R) - a1 / R,
                                   -(a2 / R) - a3 / R, 1, roots, &nq);

    int count = 0;
    if (nq != -3)
    {
        if (nq == 1)
        {
            rt[0] = roots[0];
            {
                const double at = atan(roots[0]);
                ang[0] = (a4 == 'r') ? at + at : at * 114.5915590261647;
            }
            goto filter_loop;
        }
        if (nq == 2)
        {
            rt[0] = roots[0];
            rt[1] = roots[1];
            {
                const double at = atan(roots[0]);
                ang[0] = (a4 == 'r') ? at + at : at * 114.5915590261647;
            }
            {
                const double at = atan(roots[1]);
                ang[1] = (a4 == 'r') ? at + at : at * 114.5915590261647;
            }
        filter_loop:
            for (int i = 0; i < nq; i++)
            {
                const double t = rt[i];
                const double av = ang[i];
                if (a5 == 0)
                {
                    count = nq;
                    if (t > -1.0)
                    {
                        if (t >= -1.0 && t < 0.0)
                        {
                            ang[i] = (a4 == 'r') ? av + PI + PI : av + 360.0;
                        }
                    }
                    else
                    {
                        ang[i] = (a4 == 'r') ? av + PI + PI : av + 360.0;
                    }
                }
                else if (a5 == 1 || a5 == 10)
                {
                    if (t >= 0.0 && t <= 1.0)
                    {
                        if (a5 == 1 ||
                            ((a4 == 'r') ? 1.5707963267948966 : 90.0) - a6 >= av)
                        {
                            rt[count] = t;
                            ang[count] = av;
                            count++;
                        }
                    }
                }
                else if (a5 == -11)
                {
                    if (fabs(t) < 1.0 &&
                        ((a4 == 'r') ? 1.5707963267948966 : 90.0) - a6 >= fabs(av))
                    {
                        ang[count] = av;
                        rt[count] = t;
                        count++;
                    }
                }
                else
                {
                    count = nq;
                }
            }
        }
    }

    const double qa0 = ang[0];
    const double qa1 = ang[1];
    const double qr0 = rt[0];
    const double qr1 = rt[1];
    *a7 = count;
    if (count == 1)
    {
        a8[0] = qa0;
        a9[0] = qr0;
    }
    else if (count == 2)
    {
        if (qa1 < qa0)
        {
            a8[0] = qa1;
            a8[1] = qa0;
            a9[0] = qr1;
            a9[1] = qr0;
        }
        else
        {
            a8[0] = qa0;
            a8[1] = qa1;
            a9[0] = qr0;
            a9[1] = qr1;
        }
    }
}
