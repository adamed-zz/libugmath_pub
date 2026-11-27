









#pragma once
#include <math.h>

namespace UGS { namespace Math {
struct Point2 { double x, y; };
struct Vector2 { double x, y; };
struct Point3 { double x, y, z; };
struct Vector3 { double x, y, z; };
} }

struct ARC_SPLINE_monge_plane_s { double lin[4]; unsigned char flag; };
struct ARC_SPLINE_1_seg_2d_s;
struct BCDF_s;

using UGS::Math::Point2;
using UGS::Math::Point3;
using UGS::Math::Vector2;
using UGS::Math::Vector3;

void ARC_SPLINE_ask_pt_and_normal_of_monge_plane(ARC_SPLINE_monge_plane_s *, Point3 *, Vector3 *);
void ARC_SPLINE_inter_2_monge_planes(ARC_SPLINE_monge_plane_s *, ARC_SPLINE_monge_plane_s *,
                                     double *, Point3 *, Vector3 *, int *);
void ARC_SPLINE_solve_quadratic_eqt(double, double, double, int, double * const, int *);
double ARC_SPLINE_ask_dist_pt_to_line_2d(Point2 const *, Point2 const *, Vector2 const *, double,
                                         Point2 *, double *, int *);
int VEC2_unitize(Vector2 const *, double, double *, Vector2 *);
int VEC3_unitize(Vector3 const *, double, double *, Vector3 *);
int VEC3_unitize(Vector3 *, double *);
void h002(double *, double const *);
void h100(double const *, double const *, double *);
void h060(double const *, double const *, double const *, double *);
void h220(double const *, double const *, double const *, double *);
void h634(double const *, double const *, double const *, double const *, int *, double *, double *);
void h805(double const *, double const *, int const *, int *);
void sub_1800032B0(double *, double, double *, double *, double, int *, double *, double *);

extern "C" void sub_180002DD0(double *a1, double a2, double *a3, double a4,
                              double *a5, double *a6);

static const double kDeg2Rad = 0.00001745329251994328;


static double CrossMag(const double *n, const double *u)
{
    double a = n[2] * u[0] - n[0] * u[2];
    double b = n[1] * u[2] - n[2] * u[1];
    double c = n[0] * u[1] - n[1] * u[0];
    return sqrt(a * a + b * b + c * c);
}

extern "C" void __fastcall sub_180001B00(double *a1, double a2, double *a3, double a4,
                                         double *a5, unsigned int *a6, double *a7)
{
    ARC_SPLINE_monge_plane_s mp1, mp2;
    double u[3];
    Point3 pt;
    Vector3 nrm;
    double out1[3], out2[3];
    double t1[3], t2[3];
    int hc = 0;
    unsigned int cnt = 0;

    *a6 = 0;
    mp1.lin[0] = mp1.lin[1] = mp1.lin[2] = mp1.lin[3] = 0.0; mp1.flag = 0;
    mp2.lin[0] = mp2.lin[1] = mp2.lin[2] = mp2.lin[3] = 0.0; mp2.flag = 0;

    double p0 = a5[0];
    double p1 = a5[1];
    double d0 = p0 + p0;
    double d1 = p1 + p1;

    sub_180002DD0(a1, a2, a3, a4, mp1.lin, mp2.lin);

    double sinr = sin(kDeg2Rad);
    ARC_SPLINE_ask_pt_and_normal_of_monge_plane(&mp1, &pt, &nrm);

    u[0] = d0; u[1] = d1; u[2] = -1.0;
    double len = 0.0;
    double s = 0.0;
    VEC3_unitize((Vector3 *)u, 1.0e-10, &len, (Vector3 *)u);
    s = (p0 * p0 + p1 * p1) / len;
    Vector3 scaled;
    scaled.x = u[0] * s; scaled.y = u[1] * s; scaled.z = u[2] * s;

    double mag = CrossMag(&nrm.x, u);
    if (sinr < mag)
    {
        h634(&pt.x, &nrm.x, &scaled.x, u, &hc, out1, out2);
        if (((hc - 1) & 0xFFFFFFFD) != 0)
        {
            sub_1800032B0(a1, a2, out1, out2, 0.0, &hc, t1, t2);
            int n = hc;
            if (n > 0)
            {
                cnt = 1;
                a7[0] = t1[0]; a7[1] = t1[1]; a7[2] = t1[2];
                if (n > 1)
                {
                    cnt = 2;
                    a7[3] = t2[0]; a7[4] = t2[1]; a7[5] = t2[2];
                }
            }
        }
    }
    {
        unsigned int v8cnt = cnt;
        double s2;
        double len2 = 0.0;
        ARC_SPLINE_ask_pt_and_normal_of_monge_plane(&mp2, &pt, &nrm);
        u[0] = d0; u[1] = d1; u[2] = -1.0;
        VEC3_unitize((Vector3 *)u, 1.0e-10, &len2, (Vector3 *)u);
        s2 = (p0 * p0 + p1 * p1) / len2;
        scaled.x = u[0] * s2; scaled.y = u[1] * s2; scaled.z = u[2] * s2;
        double mag2 = CrossMag(&nrm.x, u);
        if (sinr < mag2
            && (h634(&pt.x, &nrm.x, &scaled.x, u, &hc, out1, out2), ((hc - 1) & 0xFFFFFFFD) != 0)
            && (sub_1800032B0(a1, a2, out1, out2, 0.0, &hc, t1, t2), hc > 0))
        {
            int n2 = hc;
            double *dst = a7 + 3 * v8cnt;
            dst[0] = t1[0]; dst[1] = t1[1]; dst[2] = t1[2];
            ++v8cnt;
            if (n2 > 1)
            {
                dst[3] = t2[0]; dst[4] = t2[1]; dst[5] = t2[2];
                *a6 = v8cnt + 1;
            }
            else
                *a6 = v8cnt;
        }
        else
            *a6 = v8cnt;
    }
}
