







#include <math.h>
#include <string.h>

namespace UGS {
namespace Math {
struct Point2 {
    double x, y;
};
}
}


__declspec(dllimport) void * __cdecl SM_alloc(unsigned __int64 size);
__declspec(dllimport) void __cdecl SM_free(void *p);


void LSFIT_ellipse_func(UGS::Math::Point2 *pts, int n, int unused,
                        double *const a, double *const res, int *unused2);

double LSFIT_nonlinear_function(
    UGS::Math::Point2 *pts, int n, int m, double *const a, double *const res,
    double t1, double t2, double t3, int maxit, double eps,
    double *const o5, int i1, double step, int i2,
    int *ie1, int *ie2, double *const b, int n2, int *const work,
    double *const o4, double *const o3, double *const o2, double *const o1,
    double *const x);

void LSFIT_ellipse_to_points_2d(UGS::Math::Point2 *pts, int npts,
                                UGS::Math::Point2 *center, double *a4,
                                double *a5, double *a6, int *a7, double *a8)
{
    int ierr = 0;
    double *bbuf;
    double *xbuf;
    double coef[5] = {1.0, 0.001, 0.0, 1.0, 1.0};
    int flag;
    double ra;
    double rb;
    double ssq;
    double p1[2];
    double p2[2];
    int work[5] = {0};
    double out1[5] = {0.0};
    double out2[5] = {0.0};
    double out3[5] = {0.0};
    double out4[5] = {0.0};
    double out5[5] = {0.0};
    double *res;
    double sum = 0.0;
    double avg;
    double ssq_out;

    double *err = a8;
    *err = 0.0;
    res = (double *)SM_alloc(8 * (__int64)npts);
    bbuf = (double *)SM_alloc(sizeof(double) * (5 * npts));
    xbuf = (double *)SM_alloc(8 * (__int64)npts);
    for (int i = 0; i < npts; ++i) {
        res[i] = 0.0;
        xbuf[i] = 0.0;
    }
    for (int i = 0; i < 5 * npts; ++i) {
        bbuf[i] = 0.0;
    }
    LSFIT_ellipse_func(pts, npts, 5, coef, res, (int *)&a8);
    ssq = LSFIT_nonlinear_function(pts, npts, 5, coef, res,
                                   1.0e-14, 1.0e-14, 1.0e-14, 1200, 1.0e-15,
                                   out5, 1, 0.1, 1, &ierr, &flag, bbuf, npts,
                                   work, out4, out3, out2, out1, xbuf);
    double det = coef[0] * coef[0] - coef[1];
    if (det < 0.0) {
        center->x = (coef[2] * coef[1] - coef[3] * coef[0]) / det;
        center->y = (coef[3] - coef[2] * coef[0]) / det;
        double theta;
        if (coef[2] == 1.0) {
            theta = atan(1.0);
        } else {
            theta = 0.5 * atan(2.0 * coef[0] / (1.0 - coef[1]));
        }
        *a6 = theta;
        double v37 = -det;
        double n1 = coef[1] + 1.0;
        double disc = n1 * n1 - v37 * 4.0;
        double sd = sqrt(disc);
        double v40 = -(coef[4] * coef[1] - coef[3] * coef[3] -
                       (coef[4] * coef[0] - coef[3] * coef[2]) * coef[0] +
                       (coef[3] * coef[0] - coef[2] * coef[1]) * coef[2]) /
                     v37;
        *a4 = sqrt(v40 / ((sd + n1) * 0.5));
        double v44 = sqrt(v40 / ((n1 - sd) * 0.5));
        *a5 = v44;
        double v45 = *a4;
        double theta2;
        if (v44 - 1.0e-10 > *a4) {
            *a4 = v44;
            *a5 = v45;
            theta2 = *a6 + 1.5707963267948966;
            *a6 = theta2;
            v45 = *a4;
        } else {
            theta2 = *a6;
        }
        p1[0] = cos(theta2) * v45 + center->x;
        p1[1] = sin(theta2) * v45 + center->y;
        LSFIT_ellipse_func((UGS::Math::Point2 *)p1, 1, 5, coef, &rb,
                           (int *)&a8);
        p2[0] = cos(*a6) * *a5;
        p2[1] = sin(*a6) * *a5;
        LSFIT_ellipse_func((UGS::Math::Point2 *)p2, 1, 5, coef, &ra,
                           (int *)&a8);
        if (fabs(rb) > fabs(ra)) {
            *a6 = *a6 + 2.0 * atan(1.0);
        }
        for (int i = 0; i < npts; ++i) {
            if (fabs(res[i]) > *err) {
                *err = fabs(res[i]);
            }
            sum = sum + fabs(res[i]);
        }
        avg = sum / (double)npts;
        ssq_out = ssq;
    } else {
        *err = 1.0e19;
        avg = 1.0e19;
        ssq_out = 1.0e19;
    }
    err[1] = avg;
    err[2] = ssq_out;
    if (res) {
        SM_free(res);
    }
    if (bbuf) {
        SM_free(bbuf);
    }
    if (xbuf) {
        SM_free(xbuf);
    }
}
