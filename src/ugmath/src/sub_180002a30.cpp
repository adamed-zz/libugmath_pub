









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


static double CrossMag2(const double *n, const double *u)
{
    double a = n[2] * u[0] - n[0] * u[2];
    double b = n[1] * u[2] - n[2] * u[1];
    double c = n[0] * u[1] - n[1] * u[0];
    return sqrt(a * a + b * b + c * c);
}

extern "C" void __fastcall sub_180002A30(double *a1, double a2, double *a3, double *a4,
                                         int *a5, double *a6)
{

    *(volatile int*)a5 = 0;
    double v8 = a3[0], v9 = a3[1];
    double v10 = a4[0], v11 = a4[1];
    double n1[3], n2[3], len1 = 0.0, len2 = 0.0, tmp = 0.0;
    double s1[3], s2[3];
    double out1[3], out2[3], t1[3], t2[3];
    double sinr;

    int hc = 0;
    sinr = sin(kDeg2Rad);

    n1[0] = v8 + v8; n1[1] = v9 + v9; n1[2] = -1.0;
    VEC3_unitize((Vector3 *)n1, 1.0e-10, &len1, (Vector3 *)n1);
    double sc1 = (v8 * v8 + v9 * v9) / len1;
    s1[0] = n1[0] * sc1; s1[1] = n1[1] * sc1; s1[2] = n1[2] * sc1;

    n2[0] = v10 + v10; n2[1] = v11 + v11; n2[2] = -1.0;
    VEC3_unitize((Vector3 *)n2, 1.0e-10, &len2, (Vector3 *)n2);
    double sc2 = (v10 * v10 + v11 * v11) / len2;
    s2[0] = n2[0] * sc2; s2[1] = n2[1] * sc2; s2[2] = n2[2] * sc2;

    double mag = CrossMag2(n2, n1);
    if (sinr < mag
        && (h634(s1, n1, s2, n2, &hc, out1, out2), ((hc - 1) & 0xFFFFFFFD) != 0)
        && (sub_1800032B0(a1, a2, out1, out2, 0.0, &hc, t1, t2), hc > 0))
    {
        a6[0] = t1[0]; a6[1] = t1[1]; a6[2] = t1[2];
        if (hc <= 1)
            *a5 = 1;
        else
        {
            a6[3] = t2[0]; a6[4] = t2[1]; a6[5] = t2[2];
            *a5 = 2;
        }
    }
    else
        *a5 = 0;
    (void)tmp;
}
