









#include <math.h>
int SOLVE_function_root(double (__cdecl *f)(double, void *), void *ctx,
                        double a, double b, double tol, double *x)
{
    double fm = f(a, ctx);
    double fb = f(b, ctx);
    double fa = fm;
    if (fa > 0.0 && fb > 0.0 || fa < 0.0 && fb < 0.0)
        return -2;
    int iter = 1;
    *x = 1.0e20;
    for (; iter <= 20; ++iter)
    {
        double xm = (b + a) * 0.5;
        fm = f(xm, ctx);
        double d = fm * fm - fa * fb;
        double s = sqrt(d);
        if (!(s > 0.0))
            return iter;
        int sgn = fa >= fb ? 1 : -1;
        double xnew = (double)sgn * fm / s * (xm - a) + xm;
        if (tol >= fabs(xnew - *x))
            return iter;
        *x = xnew;
        double fnew = f(xnew, ctx);
        if (!(fnew > 0.0) && !(fnew < 0.0))
            return iter;
        if (fm >= 0.0 && fnew < 0.0 || fm < 0.0 && fnew >= 0.0)
        {
            b = *x;
            a = xm;
            fa = fm;
            fb = fnew;
        }
        else
        {
            if (fa >= 0.0 && fnew < 0.0 || fa < 0.0 && fnew >= 0.0)
            {
                b = *x;
                fb = fnew;
            }
            else
            {
                if (fb >= 0.0 && fnew < 0.0 || fb < 0.0 && fnew >= 0.0)
                {
                    a = *x;
                    fa = fnew;
                }
            }
        }
        if (tol > fabs(b - a))
            return iter;
    }
    return -1;
}
