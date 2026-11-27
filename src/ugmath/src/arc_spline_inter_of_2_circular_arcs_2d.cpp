










#include <cmath>
#include <emmintrin.h>






namespace UGS
{
namespace Math
{
struct Point2
{
    double x, y;
};
struct Vector2
{
    double x, y;
};
}
}

struct ARC_SPLINE_1_seg_2d_s
{
    int    kind;
    int    dir;
    double p0x;
    double p0y;
    double ang0;
    double ang1;
    double cx;
    double cy;
    double d0;
    double d1;
    double radius;
};


void ARC_SPLINE_inter_circular_arc_line_seg_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                                const ARC_SPLINE_1_seg_2d_s* a2,
                                                int a3, int a4, const double* const a5,
                                                int* a6, UGS::Math::Point2* a7,
                                                double* a8, int* a9,
                                                UGS::Math::Point2* a10, double* a11,
                                                int* a12, int* a13);


void ARC_SPLINE_ask_radical_axis_of_2_circles_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                                 const ARC_SPLINE_1_seg_2d_s* a2,
                                                 UGS::Math::Point2* a3,
                                                 UGS::Math::Vector2* a4,
                                                 int* a5, int* a6);



void ARC_SPLINE_ask_parm_at_a_point_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                       const UGS::Math::Point2* a2,
                                       const double* const a3,
                                       UGS::Math::Point2* a4, double* a5,
                                       int* a6, int* a7);


using UGS::Math::Point2;
using UGS::Math::Vector2;

void ARC_SPLINE_inter_of_2_circular_arcs_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                            const ARC_SPLINE_1_seg_2d_s* a2,
                                            int a3, int a4, const double* const a5,
                                            int* a6, Point2* a7, double* a8, int* a9,
                                            Point2* a10, double* a11, int* a12, int* a13)
{
    *a6 = 0;
    a7->x = 0.0;
    a7->y = 0.0;
    a8[0] = 0.0;
    a8[1] = 0.0;
    a9[0] = -1;
    a9[1] = -1;
    a10->x = 0.0;
    a10->y = 0.0;
    a11[0] = 0.0;
    a11[1] = 0.0;
    a12[1] = -1;
    a12[0] = -1;
    *a13 = 0;

    if (!a1)
    {
        *a13 = 1;
        return;
    }
    int          kind1 = a1->kind;
    const double cx1   = a1->cx;
    const double cy1   = a1->cy;
    double       r1;
    if (kind1 == 0)
    {
        r1 = 1.0e19;
    }
    else if (kind1 == 1)
    {
        r1 = a1->radius;
        if (r1 < 1.0e-10)
            kind1 = -1;
    }
    else
    {
        *a13 = 1;
        return;
    }

    int err = 0;
    if (!a2)
    {
        *a13 = 2;
        return;
    }
    int kind2 = a2->kind;
    if (kind2 == 0)
    {
    }
    else if (kind2 == 1)
    {
        if (a2->radius < 1.0e-10)
            kind2 = -1;
    }
    else
    {
        *a13 = 2;
        return;
    }

    if (kind1 != 0)
    {
        if (kind2 == 0)
        {
            ARC_SPLINE_inter_circular_arc_line_seg_2d(a1, a2, a3, a4, a5, a6, a7, a8, a9,
                                                      a10, a11, a12, a13);
            return;
        }


        Point2  P = {0.0, 0.0};
        Point2  q = {0.0, 0.0};
        Vector2 D = {0.0, 0.0};
        int rk;
        ARC_SPLINE_ask_radical_axis_of_2_circles_2d(a1, a2, &P, &D, &rk, &err);
        if (rk == 0 || rk == 3)
        {
            *a6 = 0;
            return;
        }
        if (rk == 1)
        {

            a7->x  = P.x;
            a7->y  = P.y;
            a10->x = P.x;
            a10->y = P.y;
            ARC_SPLINE_ask_parm_at_a_point_2d(a1, &P, a5, a7, a8, a9, &err);
            if (err > 0)
            {
                *a13 = 3;
                return;
            }
            if (a3 == 0)
                a9[0] = -1;
            ARC_SPLINE_ask_parm_at_a_point_2d(a2, &P, a5, a10, a8 + 1, a9 + 1, &err);
            if (err > 0)
            {
                *a13 = 4;
                return;
            }
            if (a4 == 0)
                a9[1] = -1;
            if (a9[0] == 1 || a9[1] == 1)
                *a6 = 0;
            else
                *a6 = 1;
            return;
        }


        const double dy = cy1 - P.y;
        const double dx = cx1 - P.x;
        const double d  = sqrt(dx * dx + dy * dy);
        const double t  = sqrt(fabs(r1 * r1 - d * d));
        const __m128d pv   = _mm_loadu_pd(&P.x);
        const __m128d dv   = _mm_loadu_pd(&D.x);
        const __m128d tpos = _mm_set1_pd(t);
        const __m128d tneg = _mm_set1_pd(-t);
        _mm_storeu_pd(&a7->x, _mm_add_pd(pv, _mm_mul_pd(tneg, dv)));
        _mm_storeu_pd(&a10->x, _mm_add_pd(pv, _mm_mul_pd(tpos, dv)));

        ARC_SPLINE_ask_parm_at_a_point_2d(a1, a7, a5, &q, a8, a9, &err);
        if (err > 0)
        {
            *a13 = 7;
            return;
        }
        if (a3 == 0)
            a9[0] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, a7, a5, &q, a8 + 1, a9 + 1, &err);
        if (err > 0)
        {
            *a13 = 8;
            return;
        }
        if (a4 == 0)
            a9[1] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, a10, a5, &q, a11, a12, &err);
        if (err > 0)
        {
            *a13 = 9;
            return;
        }
        if (a3 == 0)
            a12[0] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, a10, a5, &q, a11 + 1, a12 + 1, &err);
        if (err > 0)
        {
            *a13 = 10;
            return;
        }
        if (a4 == 0)
            a12[1] = -1;


        if (a9[0] == 1 || a9[1] == 1)
        {
            if (a12[0] == 1 || a12[1] == 1)
            {
                *a6 = 0;
                return;
            }
            *a6 = 1;
            const Point2 tp = *a7;
            *a7             = *a10;
            *a10            = tp;
            double td;
            td     = a8[0];
            a8[0]  = a11[0];
            a11[0] = td;
            td     = a8[1];
            a8[1]  = a11[1];
            a11[1] = td;
            int ti;
            ti     = a9[0];
            a9[0]  = a12[0];
            a12[0] = ti;
            ti     = a9[1];
            a9[1]  = a12[1];
            a12[1] = ti;
            return;
        }
        if (a12[0] == 1 || a12[1] == 1)
        {
            *a6 = 1;
            return;
        }
        *a6 = 2;
        return;
    }

    if (kind2 != 0)
    {

        Point2 q1;
        Point2 q2;
        double pa[2];
        double pb[2];
        int    sa[2];
        int    sb[2];
        ARC_SPLINE_inter_circular_arc_line_seg_2d(a2, a1, a4, a3, a5, a6, &q1, pa, sa, &q2,
                                                  pb, sb, a13);
        if (*a13 == 0)
        {
            *a7  = q2;
            *a10 = q1;
            a9[0]  = sb[0];
            a9[1]  = sb[1];
            a12[0] = sa[0];
            a12[1] = sa[1];
        }
        return;
    }
    ARC_SPLINE_inter_circular_arc_line_seg_2d(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11,
                                              a12, a13);
}
