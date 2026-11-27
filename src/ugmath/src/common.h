
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

static const double kDeg2Rad = 0.01745329251994328;
