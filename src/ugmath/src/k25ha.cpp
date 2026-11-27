












#include <cmath>
#include "iacomparameteraccess_shared.h"

double EQ_ask_number_tolerance();

static const double kNumTol = 1e-10;
static const double kPi = 3.141592653589793;
static const double kTwoPi = 6.283185307179586;
static const double kHalfPi = 1.5707963267948966;
static const double kThreeHalfPi = 4.71238898038469;
static const double kHalf = 0.5;
static const int kType0 = 0;




__declspec(noinline) void h805n(const double* a1, const double* a2, const int* a3, int* a4)
{
    (void)a3;
    const double tol = kNumTol;
    *a4 = tol >= std::fabs(*a1 - *a2);
}



void h053(const double* a1, const double* a2, double* a3);



void h224(const double* a1, const double* a2, const double* a3, double* a4);








static double h804_ask_tol(const int* mode)
{
    if (*mode == 0)
        return EQ_ask_number_tolerance();
    UGS::Part::IAcomParameterAccess* p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    if (*mode == 1)
        return p->p01();
    return p->p04();
}

__declspec(noinline) void h804(double* a1, const double* a2, const int* a3, int* a4)
{
    double tol = h804_ask_tol(a3);
    int hit = tol >= std::fabs(*a1 - a2[0]);
    if (hit)
    {
        *a4 = 2;
        *a1 = a2[0];
        return;
    }
    if (!(*a1 > a2[0]))
    {
        *a4 = 1;
        return;
    }
    tol = h804_ask_tol(a3);
    hit = tol >= std::fabs(*a1 - a2[1]);
    if (hit)
    {
        *a4 = 4;
        *a1 = a2[1];
        return;
    }
    *a4 = 3;
    if (*a1 > a2[1])
        *a4 = 5;
}



void h070(const double* a1, double* a2);

__declspec(noinline) void k25ha(double* a1, int* a2, double* a3)
{
    if (*a2 == 1)
    {
        const double t0 = a1[0];
        const double t1 = a1[1];
        a1[0] = a1[5];
        a1[1] = a1[6];
        a1[5] = t0;
        a1[6] = t1;
    }

    const double p0[2] = { a1[0], a1[1] };
    const double ctr[2] = { a1[2], a1[3] };
    const double p1[2] = { a1[5], a1[6] };
    double ang[2];
    h224(p0, p1, ctr, ang);
    const double S = ang[0];
    double E = ang[1];
    if (!(S < E))
        E += kTwoPi;
    double delta = E - S;

    const int kType = 0;
    const double cls[2] = { kPi, kTwoPi };
    int mode = 0;
    h804(&delta, cls, &kType, &mode);

    const double r = a1[4];
    const double cx = ctr[0];
    const double cy = ctr[1];
    const double x0 = std::cos(S) * r + cx;
    const double y0 = std::sin(S) * r + cy;

    double pt[6][2];
    double bx0;
    double by0;
    int npts;
    if (mode == 3)
    {
        const double m3 = S + kPi;
        const double c3 = std::cos(m3);
        const double x1 = c3 * r + cx;
        const double s3 = std::sin(m3);
        const double y1 = s3 * r + cy;
        const double hx = (x1 - x0) * kHalf;
        const double hy = (y1 - y0) * kHalf;
        const double md3 = (S + m3) * kHalf;
        const double mc = std::cos(md3);
        const double midx = mc * r + cx;
        const double ms = std::sin(md3);
        const double midy = ms * r + cy;
        pt[0][0] = midx - hx;
        pt[0][1] = midy - hy;
        pt[1][0] = midx + hx;
        pt[1][1] = midy + hy;
        pt[2][0] = x1;
        pt[2][1] = y1;

        const double x1c = std::cos(E) * r + cx;
        pt[3][0] = x1c;
        const double y1c = std::sin(E) * r + cy;
        pt[3][1] = y1c;
        const double md = (E + m3) * kHalf;
        const double dx = (x1c - x1) * kHalf;
        const double dy = (y1c - y1) * kHalf;
        const double mx = std::cos(md) * r + cx;
        const double my = std::sin(md) * r + cy;
        pt[4][0] = mx - dx;
        pt[4][1] = my - dy;
        pt[5][0] = mx + dx;
        pt[5][1] = my + dy;
        bx0 = x0;
        by0 = y0;
        npts = 6;
    }
    else if (mode == 1 || mode == 2)
    {
        const double x1c = std::cos(E) * r + cx;
        pt[0][0] = x1c;
        const double y1c = std::sin(E) * r + cy;
        pt[0][1] = y1c;
        const double md = (E + S) * kHalf;
        const double dx = (x1c - x0) * kHalf;
        const double dy = (y1c - y0) * kHalf;
        const double mx = std::cos(md) * r + cx;
        const double my = std::sin(md) * r + cy;
        pt[1][0] = mx - dx;
        pt[1][1] = my - dy;
        pt[2][0] = mx + dx;
        pt[2][1] = my + dy;
        bx0 = x0;
        by0 = y0;
        npts = 3;
    }
    else if (mode == 4 || mode == 5)
    {


        const double negr = -r;
        const double xp = r + cx;
        const double yp = r + cy;
        const double xm = negr + cx;
        const double ym = negr + cy;
        pt[0][0] = xm;
        pt[0][1] = yp;
        pt[1][0] = xm;
        pt[1][1] = ym;
        pt[2][0] = xp;
        pt[2][1] = ym;
        bx0 = xp;
        by0 = yp;
        npts = 3;
    }
    else
    {
        a3[0] = x0;
        a3[1] = y0;
        a3[2] = x0;
        a3[3] = y0;
        return;
    }

    a3[0] = bx0;
    a3[1] = by0;
    a3[2] = bx0;
    a3[3] = by0;
    for (int i = 0; i < npts; ++i)
        h070(pt[i], a3);
}
