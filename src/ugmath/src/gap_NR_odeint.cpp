



#include <math.h>

typedef void (__cdecl *NR_derivs_t)(void *, double *, double *, double *, int *);

void __cdecl NR_odeint(double *y, double x1, double x2, double eps, double h1,
                       double hmin, void *ctx, NR_derivs_t derivs, int *err)
{
    double yv = *y;
    double x = x1;
    double h = fabs(h1);
    if (!(x2 > x1))
        h = -h;
    double hnext = x2;
    int nstp = 0;
    double yscal, hw, half, quart, x0, y0, xt, yt, xm, ystep, y2, yfull, delta, ratio;
    double k0, k1, k2, k3, ka0, ka1, ka2, ka3, kb1, kb2, kb3, xn;
    int e;

    *err = -2;
    for (;;) {
    outer_top:
        derivs(ctx, &x, &yv, &k0, err);
        if (*err) {
            *err += 3;
            return;
        }
        if ((x + h - x1) * (x + h - x2) > 0.0)
            h = x2 - x;
        yscal = fabs(k0 * h) + fabs(yv) + 1e-30;
        hw = h;
        x0 = x;
        y0 = yv;
        y2 = yv;
        for (;;) {
            half = hw * 0.5;
            quart = half * 0.5;
            xt = x0 + quart;
            yt = y0 + quart * k0;
            *err = 0;
            derivs(ctx, &xt, &yt, &k1, err);
            if (*err) goto err_first;
            *err = 0;
            yt = y0 + quart * k1;
            derivs(ctx, &xt, &yt, &k2, err);
            if (*err) goto err_first;
            *err = 0;
            xm = x0 + half;
            yt = y0 + half * k2;
            derivs(ctx, &xm, &yt, &k3, err);
            if (*err) goto err_first;
            ystep = y0 + (k0 + k3 + 2.0 * (k1 + k2)) * (half / 6.0);
        second:
            x = x0 + half;
            *err = 0;
            derivs(ctx, &x, &ystep, &ka0, err);
            if (*err) goto err_second;
            *err = 0;
            xt = x + quart;
            yt = ystep + quart * ka0;
            derivs(ctx, &xt, &yt, &ka1, err);
            if (*err) goto err_later;
            *err = 0;
            yt = ystep + quart * ka1;
            derivs(ctx, &xt, &yt, &ka2, err);
            if (*err) goto err_later;
            *err = 0;
            yt = ystep + half * ka2;
            xn = x + half;
            derivs(ctx, &xn, &yt, &ka3, err);
            if (*err) goto err_later;
            y2 = ystep + (ka0 + ka3 + 2.0 * (ka1 + ka2)) * (half / 6.0);
        xcheck:
            xn = x0 + hw;
            if (xn == x0) {
                *err = 1;
                return;
            }
            x = xn;
            *err = 0;
            yt = y0 + half * k0;
            derivs(ctx, &xm, &yt, &kb1, err);
            if (*err) goto err_third;
            *err = 0;
            yt = y0 + half * kb1;
            derivs(ctx, &xm, &yt, &kb2, err);
            if (*err) goto err_third;
            *err = 0;
            yt = y0 + hw * kb2;
            derivs(ctx, &xn, &yt, &kb3, err);
            if (*err) goto err_third;
            yfull = y0 + (k0 + kb3 + 2.0 * (kb1 + kb2)) * (hw / 6.0);
        errchk:
            delta = y2 - yfull;


            ystep = delta;
            ratio = fabs(delta / yscal) / eps;
            if (ratio <= 1.0) {
                if (ratio <= 0.0006)
                    hnext = 4.0 * hw;
                else
                    hnext = exp(log(ratio) * -0.2) * (0.9 * hw);
                yv = y2 + delta * 0.06666666;
            } else {
                hw = hw * 0.9 * exp(log(ratio) * -0.25);
                continue;
            }
        after:
            h = hnext;
            if ((x - x2) * (x2 - x1) >= 0.0) {
                *err = 0;
                *y = yv;
                return;
            }
            if (hmin >= fabs(hnext)) {
                *err = 2;
                return;
            }
            *err = -2;
            if (++nstp < 10000)
                goto outer_top;
            *err = 3;
            return;

        err_first:
            if (*err + 3 >= 4) goto reduce;
            goto second;

        err_later:
            if (*err + 3 >= 4) goto reduce;
            goto xcheck;

        err_second:
            e = *err + 3;
            x = x0;
            *err = e;
            yv = y0;
            if (e == 1)
                return;
            if (e < 4) goto after;
            goto halve;

        err_third:
            e = *err + 3;
            *err = e;
            if (e >= 4) goto reduce;
            yfull = ystep;
            goto errchk;

        reduce:
            x = x0;
            yv = y0;
        halve:
            h = h * 0.5;
            *err = -1;
            if (++nstp < 10000)
                goto outer_top;
            *err = 3;
            return;
        }
    }
}
