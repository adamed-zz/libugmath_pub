









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


extern "C" void __fastcall sub_1800027A0(double *a1, double a2, double *a3, double a4,
                                         double *a5, double a6, int *a7, double *a8)
{
    const double tol[2] = { 1.0e-10, 0.001 };
    ARC_SPLINE_monge_plane_s p1, p2, p3, p4;
    Point3 pts[4];
    Vector3 nrms[4];
    int st[4];
    double t2[3];
    double tmp[3];
    int i;

    p1.lin[0] = p1.lin[1] = p1.lin[2] = p1.lin[3] = 0.0; p1.flag = 0;
    p2 = p1; p3 = p1; p4 = p1;
    for (i = 0; i < 4; ++i) st[i] = 0;
    *a7 = 0;

    sub_180002DD0(a1, a2, a3, a4, p1.lin, p4.lin);
    sub_180002DD0(a1, a2, a5, a6, p2.lin, p3.lin);




    ARC_SPLINE_inter_2_monge_planes(&p1, &p3, (double *)tol, &pts[0], &nrms[0], &st[0]);
    ARC_SPLINE_inter_2_monge_planes(&p1, &p2, (double *)tol, &pts[1], &nrms[1], &st[1]);
    ARC_SPLINE_inter_2_monge_planes(&p4, &p2, (double *)tol, &pts[2], &nrms[2], &st[2]);
    ARC_SPLINE_inter_2_monge_planes(&p4, &p3, (double *)tol, &pts[3], &nrms[3], &st[3]);

    int count = 0;
    double *dst = a8;
    for (i = 0; i < 4; ++i)
    {
        if (st[i] == 0)
        {
            int hc = 0;
            sub_1800032B0(a1, a2, &pts[i].x, &nrms[i].x, 0.0, &hc, tmp, t2);
            int n = hc;
            if (n > 0)
            {
                dst[0] = tmp[0]; dst[1] = tmp[1]; dst[2] = tmp[2];
                dst += 3;
                ++count;
                if (n > 1)
                {
                    dst[0] = t2[0]; dst[1] = t2[1]; dst[2] = t2[2];
                    dst += 3;
                    ++count;
                }
            }
        }
    }
    (void)count;
    *a7 = count;
}
