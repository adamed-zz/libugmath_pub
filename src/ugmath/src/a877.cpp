




#pragma once
namespace UGS { namespace Part {
class IAcomParameterAccess { public: static IAcomParameterAccess *GetAcomParameterAccess(); };
} }





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


void __fastcall a877(double *a1, double *a2, int *a3)
{
    const double kTwoPi = 6.283185307179586;
    double v19 = kTwoPi;
    double v30 = 0.0;
    int v34 = 0;
    int v33 = 0;

    double v22 = 0.0, v18 = 0.0;
    double v24[3], v27[3], v31[3], v32[3];
    double v20, v21, v23;

    UGS::Part::IAcomParameterAccess *p = UGS::Part::IAcomParameterAccess::GetAcomParameterAccess();
    {
        double *m = (*(double *(__fastcall **)(UGS::Part::IAcomParameterAccess *))((char *)*(void **)p + 0x138))(p);
        v22 = m[7] * a2[7] + m[6] * a2[6] + m[8] * a2[8];
    }
    h805(&v22, &v30, &v34, &v33);
    if (v33 != 1)
    {
        v18 = a1[1] - a1[0];
        h805(&v18, &v19, &v34, &v33);
        if (v33 != 1)
        {
            double *m = (*(double *(__fastcall **)(UGS::Part::IAcomParameterAccess *))((char *)*(void **)p + 0x138))(p);
            h100(m, a2, v31);
            v31[2] = 0.0;
            h220(a1 + 2, a1 + 5, a1, v24);
            h220(a1 + 2, a1 + 5, a1 + 1, v27);
            double v9 = v24[1] - a1[3];
            double v10 = a1[4] - a1[4];
            v24[0] = v24[0] - a1[2];
            double v11 = v27[0] - a1[2];
            v24[1] = v9;
            double v12 = v27[1] - a1[3];
            v24[2] = v10;
            v27[0] = v11;
            v27[2] = v10;
            v27[1] = v12;
            double *m2 = (*(double *(__fastcall **)(UGS::Part::IAcomParameterAccess *))((char *)*(void **)p + 0x138))(p);
            h100(m2 + 6, a2, v32);
            h060(v31, v24, v32, &v18);
            h060(v31, v27, v32, &v23);

            if (v22 > 0.0) { v20 = v18; v21 = v23; }
            else { v20 = v23; v21 = v18; }
            h002(&v20, &v19);
            h002(&v21, &v19);
            double v16 = v21;
            if (v20 >= v21)
                v16 = v21 + kTwoPi;
            int v17 = *a3;
            if (*a3 == 1) { *a1 = v20; v17 = *a3; }
            if (v17 == 2) a1[1] = v16;
        }
    }
}
