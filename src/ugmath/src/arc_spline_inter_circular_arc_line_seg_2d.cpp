











#include <cmath>
#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    n;
    double p_x;
    double p_y;
    double start_angle;
    double end_angle;
    double center_x;
    double center_y;
    double dir_x;
    double dir_y;
    double radius;
};

namespace UGS { namespace Math {
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };
}}

using UGS::Math::Point2;
using UGS::Math::Vector2;


void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within, double parm,
                                    Point2* pt, Vector2* tan_out, int* status);

void ARC_SPLINE_inter_line_line_2d(const double* const tol, const Point2* a, const Point2* b,
                                   int flag, Vector2* d1, Vector2* d2, Point2* out,
                                   double* t1, double* t2, int* status);

void ARC_SPLINE_ask_parm_at_a_point_2d(const ARC_SPLINE_1_seg_2d_s* seg, const Point2* pt,
                                       const double* const tol, Point2* closest, double* parm,
                                       int* flag, int* status);

double ARC_SPLINE_ask_dist_pt_to_line_seg_2d(const Point2* pt, const Point2* p1, const Point2* p2,
                                             double tol, int clamp, Point2* closest,
                                             double* t_out, int* pos, int* side);

static const double kEps    = 1.0e-10;
static const double kBigR   = 1.0e19;

void ARC_SPLINE_inter_circular_arc_line_seg_2d(
    const ARC_SPLINE_1_seg_2d_s* a1,
    const ARC_SPLINE_1_seg_2d_s* a2,
    int a3,
    int a4,
    const double* const a5,
    int* a6,
    Point2* a7,
    double* a8,
    int* a9,
    Point2* a10,
    double* a11,
    int* a12,
    int* a13)
{

    *a6 = 0;
    Point2 v63 = {0.0, 0.0};
    a7->x = 0.0;
    a7->y = 0.0;
    a8[0] = 0.0;
    a8[1] = 0.0;
    a9[0] = -1;
    a9[1] = -1;
    Point2 v66 = {0.0, 0.0};
    a10->x = 0.0;
    a10->y = 0.0;
    a11[0] = 0.0;
    Point2 v64 = {0.0, 0.0};
    Point2 v62 = {0.0, 0.0};
    double* v65 = a11 + 1;
    Vector2 v69 = {0.0, 0.0};
    a11[1] = 0.0;


    *(volatile int*)&a12[0] = -1;
    Vector2 v68 = {0.0, 0.0};
    int* v61 = a12 + 1;
    *(volatile int*)&a12[1] = -1;
    *a13 = 0;

    if (!a1)
    {
        *a13 = 1;
        return;
    }
    int kind1 = a1->type;
    Point2 v70 = {a1->center_x, a1->center_y};
    double r1;
    if (!kind1)
    {
        r1 = kBigR;

        double dead = (a1->end_angle - a1->start_angle) * (double)a1->n;
        (void)dead;
        v62.x = a1->p_x;
        v62.y = a1->p_y;
        v69.x = a1->dir_x;
        v69.y = a1->dir_y;
    }
    else
    {
        if (kind1 != 1)
        {
            *a13 = 1;
            return;
        }
        r1 = a1->radius;
        if (kEps > r1)
            kind1 = -1;
    }

    int status = 0;
    if (!a2)
    {
        *a13 = 2;
        return;
    }


    double ang2 = a2->end_angle;
    {
        double d = (a2->end_angle - a2->start_angle) * (double)a2->n;
        if (d < 0.0)
            ang2 = (double)a2->n * (d + 360.0) + a2->start_angle;
    }
    Point2 v67 = {a2->p_x, a2->p_y};
    double tmax = 0.0;
    if (a2->type != 0)
        goto a2_is_arc;
    tmax = a2->radius;
    v68.x = a2->dir_x;
    v68.y = a2->dir_y;
    v64.x = v68.x * tmax + v67.x;
    v64.y = v68.y * tmax + v67.y;
    if (*a5 >= tmax)
    {
        v64.x = v67.x + v68.x;
        v64.y = v67.y + v68.y;
    }

    if (!kind1)
    {

        double t1;
        int st_line;
        ARC_SPLINE_inter_line_line_2d(a5, (const Point2*)&v62, &v67, 1, &v69, &v68, a7, a8,
                                      &t1, &st_line);
        if (st_line)
            return;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, a7, a5, &v63, a8, a9, &status);
        if (status > 0)
        {
            *a13 = 3;
            return;
        }
        if (!a3)
            a9[0] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, a7, a5, &v63, a8 + 1, a9 + 1, &status);
        if (status > 0)
        {
            *a13 = 4;
            return;
        }
        if (!a4)
            a9[1] = -1;
        if (a9[0] == 1 || a9[1] == 1)
        {
            *a6 = 0;
            return;
        }
        *a6 = 1;
        return;
    }

    {


        int pos_scratch;
        int side_scratch;
        double dist = ARC_SPLINE_ask_dist_pt_to_line_seg_2d(&v70, &v67, &v64, *a5, 0, &v66,
                                                            (double*)&v62, &pos_scratch, &side_scratch);
        if (*a5 >= fabs(dist - r1))
        {

            *a7 = v66;
            *a10 = v66;
            ARC_SPLINE_ask_parm_at_a_point_2d(a1, &v66, a5, a7, a8, a9, &status);
            if (status > 0)
            {
                *a13 = 5;
                return;
            }
            if (!a3)
                a9[0] = -1;
            ARC_SPLINE_ask_parm_at_a_point_2d(a2, &v66, a5, a10, a8 + 1, a9 + 1, &status);
            if (status > 0)
            {
                *a13 = 6;
                return;
            }
            if (!a4)
                a9[1] = -1;
            if (a9[0] == 1 || a9[1] == 1)
            {
                *a6 = 0;
                return;
            }
            *a6 = 1;
            return;
        }
        if (dist > r1)
        {
            *a6 = 0;
            return;
        }

        double sq = sqrt(r1 * r1 - dist * dist);
        __m128d vs = _mm_set1_pd(sq);
        __m128d signmask = _mm_set_pd(-0.0, -0.0);
        __m128d neg = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(vs), _mm_castpd_ps(signmask)));
        __m128d dv = _mm_loadu_pd(&v68.x);
        __m128d foot = _mm_loadu_pd(&v66.x);
        _mm_storeu_pd(&a7->x, _mm_add_pd(_mm_mul_pd(neg, dv), foot));
        _mm_storeu_pd(&a10->x, _mm_add_pd(_mm_mul_pd(vs, dv), foot));

        ARC_SPLINE_ask_parm_at_a_point_2d(a1, a7, a5, &v63, a8, a9, &status);
        if (status > 0)
        {
            *a13 = 7;
            return;
        }
        if (!a3)
            a9[0] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, a7, a5, &v63, a8 + 1, a9 + 1, &status);
        if (status > 0)
        {
            *a13 = 8;
            return;
        }
        if (!a4)
            a9[1] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, a10, a5, &v63, a11, a12, &status);
        if (status > 0)
        {
            *a13 = 9;
            return;
        }
        if (!a3)
            a12[0] = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, a10, a5, &v63, v65, v61, &status);
        if (status > 0)
        {
            *a13 = 10;
            return;
        }
        if (!a4)
            a12[1] = -1;

        if (a9[0] == 1 || a9[1] == 1)
        {
            if (a12[0] == 1 || a12[1] == 1)
            {
                *a6 = 0;
                return;
            }

            *a6 = 1;
            Point2 tp = *a7;
            *a7 = *a10;
            *a10 = tp;
            double d0 = a8[0];
            double d1 = a8[1];
            a8[0] = a11[0];
            a8[1] = a11[1];
            a11[0] = d0;
            a11[1] = d1;
            int i0 = a9[0];
            int i1 = a9[1];
            a9[0] = a12[0];
            a9[1] = a12[1];
            a12[0] = i0;
            a12[1] = i1;
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

a2_is_arc:
    if (a2->type == 1 && !(a2->radius < kEps))
        ARC_SPLINE_evaluate_arc_seg_2d(a2, 1, ang2, &v64, (Vector2*)&v70, &status);
    *a13 = 2;
}
