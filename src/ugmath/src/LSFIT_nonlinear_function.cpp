








#include <math.h>
#include <emmintrin.h>

namespace UGS { namespace Math { struct Point2; } }
using UGS::Math::Point2;


double sub_18005FC00(int n, const double *x);
void   sub_180060000(Point2 *pts, int m, int n, double *x, double *fvec, double *fjac,
                     int ldfjac, int *iflag, double epsfcn, double *wa);
void   sub_180060490(int n, double *r, int ldr, int *ipvt, double *diag, double *qtb,
                     double delta, double *par, double *x, double *sdiag,
                     double *wa1, double *wa2);
void   sub_180061400(int m, int n, double *a, int lda, int pivot, int *ipvt,
                     int lipvt, double *rdiag, double *acnorm, double *wa);
void   LSFIT_ellipse_func(Point2 *pts, int m, int n, double * const x,
                          double * const fvec, int *iflag);

double LSFIT_nonlinear_function(Point2 *a1, int m, int n, double * const x,
        double * const fvec, double ftol, double xtol, double gtol, int maxfev,
        double epsfcn, double * const diag, int mode, double factor, int nprint,
        int *info, int *nfev, double * const fjac, int ldfjac, int * const ipvt,
        double * const qtf, double * const wa1, double * const wa2,
        double * const wa3, double * const wa4)
{
    int i, j, l;
    double actred, delta, delta2, dirder, epsmch, fnorm, fnorm1, gnorm,
        par, pnorm, prered, ratio, sum, temp, temp1, temp2, xnorm;
    int iflag, iflag2, iter;
    const double zero = 0., one = 1., p1 = .1, p5 = .5, p25 = .25, p75 = .75,
        p0001 = 1e-4;

    *info = 0;
    *nfev = 0;
    delta = zero;
    delta2 = zero;
    xnorm = zero;
    if (n <= 0)
        goto L9999;
    if (m < n)
        goto L9999;
    if (ldfjac < m)
        goto L9999;
    if (ftol < zero)
        goto L9999;
    if (xtol < zero)
        goto L9999;
    if (gtol < zero)
        goto L9999;
    if (maxfev <= 0)
        goto L9999;
    if (factor <= zero)
        goto L9999;
    if (mode == 2) {
        for (j = 0; j < n; ++j)
            if (diag[j] <= zero)
                goto L9999;
    }
    LSFIT_ellipse_func(a1, m, n, x, fvec, &iflag);
    *nfev = 1;
    fnorm = sub_18005FC00(m, fvec);
    epsmch = 1.2e-16;
    par = zero;
    iter = 1;
    iflag2 = 2;
    iflag = 2;
    sub_180060000(a1, m, n, x, fvec, fjac, ldfjac, &iflag, epsfcn, wa4);
    *nfev += n;
L30:
    if (nprint > 0) {
        iflag2 = 0;
        if ((iter - 1) % nprint == 0)
            LSFIT_ellipse_func(a1, m, n, x, fvec, &iflag);
    }
    sub_180061400(m, n, fjac, ldfjac, 1, ipvt, n, wa1, wa2, wa3);
    if (iter == 1) {
        if (mode != 2) {
#pragma loop(no_vector)
            for (j = 0; j < n; ++j) {
                diag[j] = wa2[j];
                if (wa2[j] == zero)
                    diag[j] = one;
            }
        }
        for (j = 0; j < n; ++j)
            wa3[j] = diag[j] * x[j];
        xnorm = sub_18005FC00(n, wa3);
        delta = factor * xnorm;
        delta2 = delta;
        if (delta == zero) {
            delta = factor;
            delta2 = factor;
        }
    }
    for (i = 0; i < m; ++i)
        wa4[i] = fvec[i];
    for (j = 0; j < n; ++j) {
        temp = fjac[j * m + j];
        if (temp != zero) {
            sum = zero;





            i = j;
            for (; i + 4 <= m; i += 4) {
                double s = sum;
                for (int k = 0; k < 4; ++k) {
                    volatile double wv = wa4[i + k];
                    double pr = wv * fjac[j * m + i + k];
                    volatile double pv = pr;
                    s = s + pv;
                }
                sum = s;
            }
            for (; i < m; ++i) {
                volatile double fv = fjac[j * m + i];
                sum = sum + fv * wa4[i];
            }
            temp = -sum / temp;
#pragma loop(no_vector)
            for (i = j; i < m; ++i)
                wa4[i] += fjac[j * m + i] * temp;
        }
        fjac[j * m + j] = wa1[j];
        qtf[j] = wa4[j];
    }
    gnorm = zero;
    if (fnorm != zero) {
        for (j = 0; j < n; ++j) {
            l = ipvt[j];
            if (wa2[l] != zero) {
                sum = zero;
                for (i = 0; i <= j; ++i)
                    sum += fjac[j * m + i] * (qtf[i] / fnorm);
                temp = fabs(sum / wa2[l]);


                gnorm = (gnorm >= temp) ? gnorm : temp;
            }
        }
    }
    if (gnorm <= gtol)
        *info = 4;
    if (*info != 0)
        goto L300;
    if (mode != 2) {
        for (j = 0; j < n; ++j)
            diag[j] = diag[j] > wa2[j] ? diag[j] : wa2[j];
    }
L200:
    sub_180060490(n, fjac, ldfjac, ipvt, diag, qtf, delta, &par, wa1, wa2, wa3, wa4);
    for (j = 0; j < n; ++j) {
        wa1[j] = -wa1[j];
        wa2[j] = x[j] + wa1[j];
        wa3[j] = diag[j] * wa1[j];
    }
    pnorm = sub_18005FC00(n, wa3);
    if (iter == 1 && pnorm < delta)
        delta2 = pnorm;
    LSFIT_ellipse_func(a1, m, n, wa2, wa4, &iflag);
    ++*nfev;
    fnorm1 = sub_18005FC00(m, wa4);
    actred = -one;
    if (p1 * fnorm1 < fnorm)
        actred = one - (fnorm1 / fnorm) * (fnorm1 / fnorm);
    for (j = 0; j < n; ++j) {
        wa3[j] = zero;
        l = ipvt[j];
        temp = wa1[l];
#pragma loop(no_vector)
        for (i = 0; i <= j; ++i)
            wa3[i] += fjac[j * m + i] * temp;
    }
    temp1 = sub_18005FC00(n, wa3) / fnorm;
    temp2 = sqrt(par) * pnorm / fnorm;
    prered = temp1 * temp1 + temp2 * temp2 / p5;
    dirder = -(temp1 * temp1 + temp2 * temp2);
    ratio = zero;
    if (prered != zero)
        ratio = actred / prered;
    if (ratio <= p25) {
        if (actred >= zero)
            temp = p5;
        else
            temp = p5 * dirder / (dirder + p5 * actred);
        if (p1 * fnorm1 >= fnorm || temp < p1)
            temp = p1;
        par /= temp;
        delta = temp * (delta2 < pnorm / p1 ? delta2 : pnorm / p1);
        delta2 = delta;
    } else if (par == zero || ratio >= p75) {
        delta = pnorm / p5;
        par = p5 * par;
        delta2 = delta;
    } else {
        delta = delta2;
    }
    if (ratio >= p0001) {
        for (j = 0; j < n; ++j) {
            x[j] = wa2[j];
            wa2[j] = diag[j] * x[j];
        }
        for (i = 0; i < m; ++i)
            fvec[i] = wa4[i];
        xnorm = sub_18005FC00(n, wa2);
        fnorm = fnorm1;
        ++iter;
    }
    if (fabs(actred) <= ftol && prered <= ftol && p5 * ratio <= one ||
        fabs(fnorm) <= ftol)
        *info = 1;
    if (delta <= xtol * xnorm)
        *info = 2;
    if (fabs(actred) <= ftol && prered <= ftol && p5 * ratio <= one &&
        *info == 2)
        *info = 3;
    if (*info != 0)
        goto L219;
    if (*nfev >= maxfev)
        *info = 5;
    if (fabs(actred) <= epsmch && prered <= epsmch && p5 * ratio <= one)
        *info = 6;
    if (delta <= epsmch * xnorm)
        *info = 7;
    if (gnorm <= epsmch)
        *info = 8;
    if (*info != 0)
        goto L219;
    if (ratio < p0001)
        goto L200;
    iflag2 = 2;
    iflag = 2;
    sub_180060000(a1, m, n, x, fvec, fjac, ldfjac, &iflag, epsfcn, wa4);
    *nfev += n;
    goto L30;
L300:
    if (iflag2 < 0)
        *info = iflag2;
    goto L9999;
L219:
L9999:
    if (nprint > 0)
        LSFIT_ellipse_func(a1, m, n, x, fvec, &iflag);
    return sub_18005FC00(n, fvec);
}
