























#include <math.h>

void ARC_SPLINE_solve_quadratic_eqt(double a, double b, double c, int mode,
                                    double* const roots, int* nroots)
{
    const double eps = 1e-12;
    if (mode == 1)
    {

        double norm = sqrt(b * b + c * c + a * a);
        if (norm < eps)
        {
            *nroots = -3;
            return;
        }
        c /= norm;
        b /= norm;
        a /= norm;
    }

    if (fabs(a) < eps)
    {

        if (fabs(b) < eps)
        {

            *nroots = (fabs(c) < eps) ? -3 : 0;
            return;
        }
        else
        {
            *nroots = 1;
            roots[0] = roots[1] = -c / b;
            return;
        }
    }

    double disc = b * b - 4.0 * a * c;
    if (fabs(disc) < 1e-24)
        disc = 0.0;
    double twoa = a + a;
    if (disc >= 0.0)
    {

        double s = sqrt(disc);
        double q;
        if (b >= 0.0)
            q = -b - s;
        else
            q = s - b;
        double x1 = q / twoa;
        roots[0] = x1;
        if (fabs(x1) < eps)
        {
            roots[0] = 0.0;
            roots[1] = -b / a;
        }
        else
        {
            roots[1] = c / (x1 * a);
        }
        *nroots = 2;
    }
    else
    {

        roots[0] = -b / twoa;
        roots[1] = sqrt(-disc) / twoa;
        *nroots = -2;
    }
}
