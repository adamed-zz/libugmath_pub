























#include <cmath>
#include <intrin.h>

namespace UGS
{
namespace Math
{
struct alignas(16) Point2
{
    double x;
    double y;
};
struct alignas(16) Vector2
{
    double x;
    double y;
};
}
}


struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double parm0;
    double parm1;
    double center_x;
    double center_y;
    double line_dx;
    double line_dy;
    double radius;
    double radius2;
};
static_assert(sizeof(ARC_SPLINE_1_seg_2d_s) == 0x58, "seg layout");

using UGS::Math::Point2;
using UGS::Math::Vector2;


int VEC2_unitize(const Vector2* u, double tol, double* len_out, Vector2* out);
void ARC_SPLINE_inter_line_line_2d(const double* const a1, const Point2* a2,
                                   const Point2* a3, int a4, Vector2* a5, Vector2* a6,
                                   Point2* a7, double* a8, double* a9, int* a10);
void ARC_SPLINE_cre_circle_thru_3_points_2d(const Point2* a1, const Point2* a2,
                                            const Point2* a3, const double* const a4,
                                            ARC_SPLINE_1_seg_2d_s* a5, int* a6);
void ARC_SPLINE_ask_tangents_thru_a_point_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                             const Point2* a2, int a3,
                                             const double* const a4, int* a5,
                                             Point2* a6, Point2* a7, double* a8,
                                             int* a9, int* a10);
void ARC_SPLINE_inter_of_2_circular_arcs_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                            const ARC_SPLINE_1_seg_2d_s* a2, int a3,
                                            int a4, const double* const a5, int* a6,
                                            Point2* a7, double* a8, int* a9,
                                            Point2* a10, double* a11, int* a12,
                                            int* a13);

static void __declspec(noinline) __cdecl cre_tangent_work(
    const Point2* a1, const Point2* a2, const ARC_SPLINE_1_seg_2d_s* a3,
    const double* const a4, int* a5, Point2* a6, Point2* a7,
    ARC_SPLINE_1_seg_2d_s* a8, ARC_SPLINE_1_seg_2d_s* a9, int* a10, char* P);


void __cdecl ARC_SPLINE_cre_circle_thru_2_points_tangent_to_circle(
    const Point2* a1, const Point2* a2, const ARC_SPLINE_1_seg_2d_s* a3,
    const double* const a4, int* a5, Point2* a6, Point2* a7,
    ARC_SPLINE_1_seg_2d_s* a8, ARC_SPLINE_1_seg_2d_s* a9, int* a10)
{
    char* const P = (char*)_AddressOfReturnAddress() + 8;

    *(void**)(P + 0x18) = (void*)&ARC_SPLINE_cre_circle_thru_2_points_tangent_to_circle;
    cre_tangent_work(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, P);
}

static void __declspec(noinline) __cdecl cre_tangent_work(
    const Point2* a1, const Point2* a2, const ARC_SPLINE_1_seg_2d_s* a3,
    const double* const a4, int* a5, Point2* a6, Point2* a7,
    ARC_SPLINE_1_seg_2d_s* a8, ARC_SPLINE_1_seg_2d_s* a9, int* a10, char* P)
{

    int*    const hSt  = (int*)(P + 0x00);
    double* const hLen = (double*)(P + 0x08);
    double* const hD   = (double*)(P + 0x10);
    int*    const h3   = (int*)(P + 0x20);
    int*    const hErr = (int*)(P + 0x28);
    int*    const hCnt = (int*)(P + 0x30);


    const Point2* const               p1   = a1;
    const Point2* const               p2   = a2;
    const ARC_SPLINE_1_seg_2d_s* const cir  = a3;
    const double* const               tol  = a4;
    int* const                        nout = a5;
    Point2* const                     out1 = a6;

    ARC_SPLINE_1_seg_2d_s tmpseg;
    double                parm2[2];
    double                parm1[2];
    Point2                pa;
    Point2                isect;
    Point2                center;
    Vector2               normal;
    Vector2               dirB;
    Vector2               dirA;
    double                tbuf[2];
    Vector2               chord;
    Point2                mid;
    Point2                p3;

    *nout = 0;
    *(long long*)&out1->x = 0;
    *(long long*)&out1->y = 0;
    center.x = 0.0;
    center.y = 0.0;
    *(long long*)&a7->x = 0;
    *(long long*)&a7->y = 0;
    for (int i = 0; i < 11; ++i)
        ((long long*)a8)[i] = 0;
    for (int i = 0; i < 11; ++i)
        ((long long*)a9)[i] = 0;
    *a10 = 0;

    chord.x = p2->x - p1->x;
    chord.y = p2->y - p1->y;
    VEC2_unitize(&chord, 1.0e-10, hLen, &chord);

    mid.x = 0.5 * (p1->x + p2->x);
    mid.y = 0.5 * (p1->y + p2->y);
    normal.x = -chord.y;
    normal.y = chord.x;

    *hErr = 0;

    if (!cir)
    {
        *a10 = 1;
        return;
    }

    int    type = cir->type;
    center.x    = cir->center_x;
    center.y    = cir->center_y;
    double radius;
    if (type == 0)
    {
        radius = 1.0e19;
    }
    else if (type == 1)
    {


        radius = cir->radius;
        if (!(radius < 1.0e-10))
        {
            *a10 = 1;
            return;
        }
    }
    else
    {
        *a10 = 1;
        return;
    }

    const double c2 = tol[0];

    double dx1 = center.x - p1->x;
    double dy1 = center.y - p1->y;
    double d1  = sqrt(dx1 * dx1 + dy1 * dy1);
    int    s1  = 0;
    if (!(c2 >= fabs(d1 - radius)))
        s1 = (radius > d1) ? -1 : 1;

    double dx2 = center.x - p2->x;
    double dy2 = center.y - p2->y;
    double d2  = sqrt(dx2 * dx2 + dy2 * dy2);
    int    s2;
    if (!(c2 >= fabs(d2 - radius)))
        s2 = (radius > d2) ? -1 : 1;
    else
        s2 = 0;

    if ((s1 == -1 && s2 == 1) || (s2 == -1 && s1 == 1))
    {
        *nout = 0;
        return;
    }

    if (s1 == 0)
    {

        dirA.x = p1->x - center.x;
        dirA.y = p1->y - center.y;
        VEC2_unitize(&dirA, 1.0e-10, hLen, &dirA);
        ARC_SPLINE_inter_line_line_2d(tol, p1, &mid, 1, &dirA, &normal, &isect,
                                      tbuf, hD, hSt);
        out1->x = p1->x;
        out1->y = p1->y;
        p3.x = 2.0 * tbuf[1] * dirA.x + p1->x;
        p3.y = 2.0 * tbuf[1] * dirA.y + p1->y;
        ARC_SPLINE_cre_circle_thru_3_points_2d(p1, p2, &p3, tol, a8, h3);
        if (*h3 == 0)
            *nout = 1;
        return;
    }

    if (s2 == 0)
    {

        dirB.x = p2->x - center.x;
        dirB.y = p2->y - center.y;
        VEC2_unitize(&dirB, 1.0e-10, hLen, &dirB);
        ARC_SPLINE_inter_line_line_2d(tol, p2, &mid, 1, &dirB, &normal, &isect,
                                      tbuf, hD, hSt);
        out1->x = p2->x;
        out1->y = p2->y;
        p3.x = 2.0 * tbuf[1] * dirB.x + p2->x;
        p3.y = 2.0 * tbuf[1] * dirB.y + p2->y;
        ARC_SPLINE_cre_circle_thru_3_points_2d(p1, p2, &p3, tol, a8, h3);
        if (*h3 == 0)
            *nout = 1;
        return;
    }


    ARC_SPLINE_cre_circle_thru_3_points_2d(p1, p2, &center, tol, &tmpseg, h3);
    isect.x = 0.0;
    isect.y = 0.0;
    pa.x    = 0.0;
    pa.y    = 0.0;
    p3.x    = 0.0;
    p3.y    = 0.0;
    ARC_SPLINE_inter_of_2_circular_arcs_2d(cir, &tmpseg, 0, 0, tol, hSt, &p3,
                                           parm1, (int*)tbuf, &pa, parm2, (int*)hD,
                                           hErr);
    if (*hErr > 0 || *hSt < 2)
    {
        *a10 = 1;
        return;
    }
    mid.x = pa.x - p3.x;
    mid.y = pa.y - p3.y;
    VEC2_unitize((Vector2*)&mid, 1.0e-10, hLen, (Vector2*)&mid);

    ARC_SPLINE_inter_line_line_2d(tol, p1, &p3, 1, &chord, (Vector2*)&mid, &isect,
                                  tbuf, hD, hSt);
    if (*hSt == 2)
    {
        *a10 = 1;
        return;
    }
    Point2* const out2 = a7;
    if (*hSt == 1)
    {
        out1->x = radius * normal.x + center.x;
        out1->y = radius * normal.y + center.y;
        out2->x = -radius * normal.x + center.x;
        out2->y = -radius * normal.y + center.y;
    }
    else
    {
        ARC_SPLINE_ask_tangents_thru_a_point_2d(cir, &isect, 0, tol, hCnt, out1, out2,
                                                parm1, hSt, hErr);
        if (*hErr > 0 || *hCnt < 2)
        {
            *a10 = 2;
            return;
        }
    }
    ARC_SPLINE_cre_circle_thru_3_points_2d(p1, p2, out1, tol, a8, h3);
    ARC_SPLINE_cre_circle_thru_3_points_2d(p1, p2, out2, tol, a9, h3);

}
