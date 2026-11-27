










#include <math.h>
#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    sense;
    double x;
    double y;
    double parm0;
    double parm1;
    double cx;
    double cy;
    double dirx;
    double diry;
    double radius;
    double radius2;
};

namespace UGS { namespace Math {
struct Point2  { double x, y; };
struct Vector2 { double x, y; };
}}

using UGS::Math::Point2;
using UGS::Math::Vector2;


__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file_name, int line,
                                                  const char* message, ...);


__declspec(dllimport) int VEC2_unitize(const Vector2* u, double tol, double* len, Vector2* out);
__declspec(dllimport) void ARC_SPLINE_cre_offset_circle_2d(ARC_SPLINE_1_seg_2d_s* s, double off,
                                                           double tol, ARC_SPLINE_1_seg_2d_s* out);
__declspec(dllimport) void ARC_SPLINE_inter_of_2_circular_arcs_2d(
    const ARC_SPLINE_1_seg_2d_s* s1, const ARC_SPLINE_1_seg_2d_s* s2, int a3, int a4,
    const double* const tols, int* num, Point2* p1, double* d1, int* c1,
    Point2* p2, double* d2, int* c2, int* status);
__declspec(dllimport) int ARC_SPLINE_ask_3pts_collinearity_2d(
    const Point2* p0, const Point2* p1, const Point2* p2,
    const double* const tols, int flag, int* status);
__declspec(dllimport) void ARC_SPLINE_cre_circle_from_chord_end_data_2d(
    const Point2* p0, const Vector2* t0, const Point2* p1, const Vector2* t1,
    int dir, double* chord_radius, ARC_SPLINE_1_seg_2d_s* out, int* status);

static const char* const kFile =
    "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c";

extern "C" void __fastcall sub_180002020(ARC_SPLINE_1_seg_2d_s* a1, ARC_SPLINE_1_seg_2d_s* a2,
                                         double a3, double* a4, int a5, int a6, int a7, int* a8,
                                         ARC_SPLINE_1_seg_2d_s* a9, Point2* a10)
{
    const double tol = 1.0e-10;
    const double line_r = 1.0e19;
    double cx1 = 0.0, cy1 = 0.0;
    double cx2 = 0.0, cy2 = 0.0;
    double r1 = 0.0, r2 = 0.0;
    int type1 = -1, type2 = -1;
    int loc1 = 0, loc2 = 0;
    Point2 i1 = {0.0, 0.0}, i2 = {0.0, 0.0};
    double d1 = 0.0, d2 = 0.0;
    int c1 = 0, c2 = 0;
    Vector2 u1 = {0.0, 0.0}, u2 = {0.0, 0.0};
    Vector2 v1 = {0.0, 0.0}, v2 = {0.0, 0.0};
    Vector2 v3 = {0.0, 0.0}, v4 = {0.0, 0.0};
    double dummy_len = 0.0;
    int local_status = 0;
    double chord_r = 0.0;
    int dir;
    ARC_SPLINE_1_seg_2d_s seg1, seg2;

    if (MACH__checking_level > 0 && a3 < a4[0])
        ERROR_assertion_failed(kFile, 13563, "%s", "( given_radius >= tols[0] )");


    if (a1 == nullptr)
    {
        cx1 = 0.0; cy1 = 0.0;
        loc1 = 1;
    }
    else
    {
        type1 = a1->type;
        cx1 = a1->cx;
        cy1 = a1->cy;
        if (type1 == 0)
        {
            r1 = line_r;
        }
        else if (type1 == 1)
        {
            r1 = a1->radius;
            if (tol > r1)
                type1 = -1;
        }
        else
        {
            loc1 = 2;
            r1 = 0.0;
        }
    }
    if (MACH__checking_level > 0 && (loc1 != 0 || type1 != 1 || !(r1 >= a4[0])))
        ERROR_assertion_failed(kFile, 13575, "%s",
                               "( local_status_flag == 0 && type_1 == 1 && radius_1 >= tols[0] )");


    if (a2 == nullptr)
    {
        cx2 = 0.0; cy2 = 0.0;
        loc2 = 1;
    }
    else
    {
        type2 = a2->type;
        cx2 = a2->cx;
        cy2 = a2->cy;
        if (type2 == 0)
        {
            r2 = line_r;
        }
        else if (type2 == 1)
        {
            r2 = a2->radius;
            if (tol > r2)
                type2 = -1;
        }
        else
        {
            loc2 = 2;
            r2 = 0.0;
        }
    }
    if (MACH__checking_level > 0 && (loc2 != 0 || type2 != 1 || !(r2 >= a4[0])))
        ERROR_assertion_failed(kFile, 13584, "%s",
                               "( local_status_flag == 0 && type_2 == 1 && radius_2 >= tols[0] )");


    double s1 = (a7 == -3 || a7 == 1) ? -a3 : a3;
    double s2 = (a7 == -3 || a7 == -1) ? -a3 : a3;
    ARC_SPLINE_cre_offset_circle_2d(a1, s1, a4[0], &seg1);
    ARC_SPLINE_cre_offset_circle_2d(a2, s2, a4[0], &seg2);

    ARC_SPLINE_inter_of_2_circular_arcs_2d(&seg1, &seg2, a5, a6, a4, a8,
                                           &i1, &d1, &c1, &i2, &d2, &c2, &local_status);
    if (*a8 == 0)
        return;


    u1.x = cx1 - i1.x;
    u1.y = cy1 - i1.y;
    VEC2_unitize(&u1, tol, &dummy_len, &u1);
    a10[0].x = i1.x + s1 * u1.x;
    a10[0].y = i1.y + s1 * u1.y;

    u2.x = cx2 - i1.x;
    u2.y = cy2 - i1.y;
    VEC2_unitize(&u2, tol, &dummy_len, &u2);
    a10[1].x = i1.x + s2 * u2.x;
    a10[1].y = i1.y + s2 * u2.y;

    ARC_SPLINE_ask_3pts_collinearity_2d(&i1, &a10[0], &a10[1], a4, 2, &a7);
    if (a7 == -1)
        a7 = 0;
    v1.x = -u1.y; v1.y = u1.x;
    if (a7 == 1)
    {
        v1.x = u1.y;
        v1.y = -u1.x;
    }
    v2.x = -u2.y; v2.y = u2.x;
    if (a7 == 1)
    {
        v2.x = u2.y;
        v2.y = -u2.x;
        dir = -1;
    }
    else
    {
        dir = (a7 == 0) ? 1 : -1;
    }
    chord_r = -1.0;
    ARC_SPLINE_cre_circle_from_chord_end_data_2d(&a10[0], &v1, &a10[1], &v2, dir, &chord_r,
                                                 a9, &local_status);
    if (MACH__checking_level > 0 && local_status != 0)
        ERROR_assertion_failed(kFile, 13719, "%s", "( local_status_flag == 0 )");
    if (*a8 != 2)
        return;


    u1.x = cx1 - i2.x;
    u1.y = cy1 - i2.y;
    VEC2_unitize(&u1, tol, &dummy_len, &u1);
    a10[2].x = i2.x + s1 * u1.x;
    a10[2].y = i2.y + s1 * u1.y;

    u2.x = cx2 - i2.x;
    u2.y = cy2 - i2.y;
    VEC2_unitize(&u2, tol, &dummy_len, &u2);
    a10[3].x = i2.x + s2 * u2.x;
    a10[3].y = i2.y + s2 * u2.y;

    ARC_SPLINE_ask_3pts_collinearity_2d(&i2, &a10[2], &a10[3], a4, 2, &a7);
    if (a7 == -1)
        a7 = 0;
    v3.x = -u1.y; v3.y = u1.x;
    if (a7 == 1)
    {
        v3.x = u1.y;
        v3.y = -u1.x;
    }
    v4.x = -u2.y; v4.y = u2.x;
    if (a7 == 1)
    {
        v4.x = u2.y;
        v4.y = -u2.x;
    }
    dir = (a7 == 0) ? 1 : -1;
    chord_r = -1.0;
    ARC_SPLINE_cre_circle_from_chord_end_data_2d(&a10[2], &v3, &a10[3], &v4, dir, &chord_r,
                                                 a9 + 1, &local_status);
    if (MACH__checking_level > 0 && local_status != 0)
        ERROR_assertion_failed(kFile, 13797, "%s", "( local_status_flag == 0 )");
}
