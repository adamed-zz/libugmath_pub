















#include <cmath>
#include <cstring>
#include <emmintrin.h>

extern "C" {

extern double g_ugm_hlr_E06C0;
extern double g_ugm_hlr_E06C8;
extern double g_ugm_hlr_E06D0;
extern double g_ugm_hlr_E06D8;
extern double g_ugm_hlr_E06B0;
extern int    g_ugm_hlr_vloc_norm;
extern int    g_ugm_hlr_E0584;
extern void sub_180049F60(double* a1);


double g_ugm_hlr_plane[12] = {0.0};
double g_ugm_hlr_win[5] = {0.0};
}



static inline double b15_add(double a, double b)
{
    if (a != a) return a + a;
    if (b != b) return b + b;
    return a + b;
}

void HLR_FACET_clipping(double const* const a1)
{
    const double x0 = a1[0], x1 = a1[1], y0 = a1[2], y1 = a1[3];
    if (x0 == 0.0 && x1 == 0.0 && y0 == 0.0 && y1 == 0.0)
        return;

    g_ugm_hlr_E0584 = 1;

    double t0 = fabs(x0) * 3.0 / 17000000.0;
    if (t0 < 0.0000001) t0 = 0.0000001;
    double t1 = fabs(x1) * 3.0 / 17000000.0;
    if (t1 < 0.0000001) t1 = 0.0000001;
    double t2 = fabs(y0) * 3.0 / 17000000.0;
    if (t2 < 0.0000001) t2 = 0.0000001;
    double t3 = fabs(y1) * 3.0 / 17000000.0;
    if (t3 < 0.0000001) t3 = 0.0000001;



    double xlo, xhi, ylo, yhi;
    if (!(y0 > x0))
    {
        xhi = b15_add(x0, t0);
        xlo = y0 - t2;
    }
    else
    {
        xlo = x0 - t0;
        xhi = b15_add(y0, t2);
    }
    if (!(y1 > x1))
    {
        ylo = y1 - t3;
        yhi = b15_add(x1, t1);
    }
    else
    {
        ylo = x1 - t1;
        yhi = b15_add(y1, t3);
    }

    g_ugm_hlr_E06C0 = xlo;
    g_ugm_hlr_E06D0 = xhi;
    g_ugm_hlr_E06C8 = ylo;
    g_ugm_hlr_E06D8 = yhi;

    double* P = g_ugm_hlr_plane;
    if (g_ugm_hlr_vloc_norm)
    {
        const double sz = g_ugm_hlr_E06B0;
        const double dz = -sz;
        const double a = dz * xlo, b = dz * ylo, c = dz * yhi;
        const double d = dz * xhi;

        P[0] = dz * yhi - dz * ylo;
        P[1] = a - a;
        P[2] = ylo * xlo - yhi * xlo;
        sub_180049F60(P);

        double* Q = P + 6;
        Q[0] = b - c;
        Q[1] = d - d;
        Q[2] = yhi * xhi - ylo * xhi;
        sub_180049F60(Q);

        double* R = P + 3;
        R[0] = b - b;
        R[1] = d - a;
        R[2] = ylo * xlo - ylo * xhi;
        sub_180049F60(R);

        double* S = P + 9;
        S[0] = c - c;
        S[1] = a - d;
        S[2] = yhi * xhi - yhi * xlo;
        sub_180049F60(S);

        const double px = xlo, py = ylo, ph = xhi, pv = yhi;
        ylo = py / sz;
        xlo = px / sz;
        yhi = pv / sz;
        xhi = ph / sz;
        g_ugm_hlr_E06C8 = ylo;
        g_ugm_hlr_E06C0 = xlo;
        g_ugm_hlr_E06D8 = yhi;
        g_ugm_hlr_E06D0 = xhi;
    }

    double* C = g_ugm_hlr_win;
    C[0] = b15_add(xhi, xlo) * 0.5;
    C[3] = (xhi - xlo) * 0.5;
    C[4] = (yhi - ylo) * 0.5;
    C[1] = (yhi + ylo) * 0.5;
    C[2] = C[4] * C[4] + C[3] * C[3];
}
