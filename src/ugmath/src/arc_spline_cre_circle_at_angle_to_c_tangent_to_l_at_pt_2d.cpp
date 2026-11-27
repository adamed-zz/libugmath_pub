




















#include <math.h>

namespace UGS
{
namespace Math
{
struct Point2
{
    double x;
    double y;
};
struct Vector2
{
    double x;
    double y;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int    tag;
    int    sense;
    double base_x;
    double base_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double d38;
    double d40;
    double radius1;
    double radius2;
};




void sub_180002F40(UGS::Math::Point2*  pt,
                   UGS::Math::Vector2* dir,
                   UGS::Math::Point2*  center,
                   double              radius,
                   double              angle_deg,
                   double*             tol,
                   int*                count,
                   double*             radii,
                   int*                senses,
                   int*                flag,
                   int*                scratch,
                   int*                type);


void ARC_SPLINE_ask_parm_at_a_point_2d(const ARC_SPLINE_1_seg_2d_s* seg,
                                       const UGS::Math::Point2*     pt,
                                       const double* const          tol,
                                       UGS::Math::Point2*           out_pt,
                                       double*                      parm,
                                       int*                         found,
                                       int*                         status);


void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg,
                                    int                          deriv,
                                    double                       parm,
                                    UGS::Math::Point2*           out_pt,
                                    UGS::Math::Vector2*          out_vec,
                                    int*                         status);


void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(const UGS::Math::Point2*  point,
                                                        const UGS::Math::Vector2* tangent,
                                                        double                    radius,
                                                        int                       sense,
                                                        ARC_SPLINE_1_seg_2d_s*    seg);


void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2*  p1,
                                const UGS::Math::Point2*  p2,
                                const UGS::Math::Vector2* fallback_dir,
                                ARC_SPLINE_1_seg_2d_s*    seg);


void h053(const double* a1, const double* a2, double* a3);


#ifdef ARC_SPLINE_SELFTEST

extern int MACH__checking_level;
void __cdecl ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);
void __cdecl ERROR_internal(const char* file, int line, const char* fmt, ...);
#else
__declspec(dllimport) extern int MACH__checking_level;

__declspec(dllimport) void __cdecl
ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);

__declspec(dllimport) __declspec(noreturn) void __cdecl
ERROR_internal(const char* file, int line, const char* fmt, ...);
#endif

static const char* const kSrcFile =
    "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c";

void __cdecl ARC_SPLINE_cre_circle_at_angle_to_c_tangent_to_l_at_pt_2d(
    UGS::Math::Point2*     a1,
    UGS::Math::Vector2*    a2,
    ARC_SPLINE_1_seg_2d_s* a3,
    double                 a4,
    double*                a5,
    int*                   a6,
    ARC_SPLINE_1_seg_2d_s* a7,
    ARC_SPLINE_1_seg_2d_s* a8,
    int*                   a9)
{

    ARC_SPLINE_1_seg_2d_s* const seg1 = a7;
    ARC_SPLINE_1_seg_2d_s* const seg2 = a8;
    int* const                   np   = a6;
    int* const                   code = a9;

    *np   = 0;
    *code = 0;


    double             radii[2];
    UGS::Math::Point2  work_pt;
    UGS::Math::Vector2 tangent;
    double             parm;
    double             orient;

    int* const    status   = (int*)&a6;
    int* const    found    = (int*)&a9;
    double* const dot      = (double*)&a6;
    double* const cross    = (double*)&a9;
    int* const    type     = (int*)&parm;
    int* const    senses   = (int*)&tangent;

    *type = 0;


    double angle = a4;
    if (a5[1] >= fabs(a4 - 0.0))
    {
        angle = 0.0;
    }
    else if (a5[1] >= fabs(a4 - 180.0))
    {
        angle = 180.0;
    }
    else if (a4 < 0.0 || a4 > 180.0)
    {
        ERROR_internal(kSrcFile, 15228, "The input value of the angle is not valid.");
    }

    if (MACH__checking_level > 0 && (!seg1 || !seg2))
    {
        ERROR_assertion_failed(kSrcFile, 15233, "%s", "seg_ptr_1 && seg_ptr_2");
    }

    *status = 0;

    if (!a3)
    {
        *code = 1;
        return;
    }

    work_pt = *(const UGS::Math::Point2*)&a3->center_x;
    double    radius;
    const int tag = a3->tag;
    if (tag == 0)
    {
        radius = 1.0e19;
    }
    else if (tag == 1)
    {
        radius = a3->radius1;
    }
    else
    {
        *code = 1;
        return;
    }

    sub_180002F40(a1, a2, &work_pt, radius, angle, a5, np, radii, senses, found, (int*)&orient,
                  type);

    if (*found == 0)
    {

        work_pt = UGS::Math::Point2{0.0, 0.0};
        tangent = UGS::Math::Vector2{0.0, 0.0};

        ARC_SPLINE_ask_parm_at_a_point_2d(a3, a1, a5, &work_pt, &parm, found, status);
        if (*status > 0)
        {
            *code = 2;
            return;
        }

        if (a3->tag == 0)
        {
            tangent.x = a3->d38;
            tangent.y = a3->d40;
        }
        else
        {
            ARC_SPLINE_evaluate_arc_seg_2d(a3, 1, parm, &work_pt, &tangent, status);
            if (*status > 0)
            {
                *code = 3;
                return;
            }
        }

        *dot   = a2->y * tangent.y + a2->x * tangent.x;
        *cross = a2->y * tangent.x - a2->x * tangent.y;
        h053(cross, dot, &parm);

        const double deg = parm * 57.29577951308235;
        if (a5[1] >= fabs(deg - angle) || a5[1] >= fabs(deg - (180.0 - angle)))
        {
            *np = 3;
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(a1, a2, radius, 1, seg1);
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(a1, a2, radius, -1, seg2);
        }
    }
    else
    {
        if (*type == 1)
        {
            ARC_SPLINE_cre_strt_seg_2d(a1, a1, a2, seg1);
            *np = 1;
        }
        else if (*np > 0)
        {
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(a1, a2, radii[0], senses[0], seg1);
            if (*np > 1)
            {
                ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(a1, a2, radii[1], senses[1], seg2);
            }
        }
    }
}
