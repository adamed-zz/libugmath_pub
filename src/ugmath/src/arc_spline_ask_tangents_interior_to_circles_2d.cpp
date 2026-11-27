















#include <cmath>
#include <emmintrin.h>

struct ARC_SPLINE_1_seg_2d_s
{
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    double center_x;
    double center_y;
    double line_dx;
    double line_dy;
    double radius;
    double radius2;
};

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

using UGS::Math::Point2;
using UGS::Math::Vector2;


void ARC_SPLINE_ask_parm_at_a_point_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                       const Point2* a2,
                                       const double* const a3,
                                       Point2* a4,
                                       double* a5,
                                       int* a6,
                                       int* a7);
void ARC_SPLINE_ask_tangents_thru_a_point_2d(const ARC_SPLINE_1_seg_2d_s* a1,
                                             const Point2* a2,
                                             int a3,
                                             const double* const a4,
                                             int* a5,
                                             Point2* a6,
                                             Point2* a7,
                                             double* a8,
                                             int* a9,
                                             int* a10);
void ARC_SPLINE_cre_strt_seg_2d(const Point2* a1,
                                const Point2* a2,
                                const Vector2* a3,
                                ARC_SPLINE_1_seg_2d_s* a4);

void ARC_SPLINE_ask_tangents_interior_to_circles_2d(
    ARC_SPLINE_1_seg_2d_s* a1,
    ARC_SPLINE_1_seg_2d_s* a2,
    int a3,
    int a4,
    double* a5,
    int* a6,
    ARC_SPLINE_1_seg_2d_s* a7,
    ARC_SPLINE_1_seg_2d_s* a8,
    double* a9,
    double* a10,
    int* a11)
{
    int dir1 = a1->dir;


    *a6 = 0;
    a7->type = 0;
    a7->dir = 0;
    a7->base_x = 0.0;
    a7->base_y = 0.0;
    a7->start = 0.0;
    a7->end = 0.0;
    a7->center_x = 0.0;
    a7->center_y = 0.0;
    a7->line_dx = 0.0;
    a7->line_dy = 0.0;
    a7->radius = 0.0;
    a7->radius2 = 0.0;
    a8->type = 0;
    a8->dir = 0;
    a8->base_x = 0.0;
    a8->base_y = 0.0;
    a8->start = 0.0;
    a8->end = 0.0;
    a8->center_x = 0.0;
    a8->center_y = 0.0;
    a8->line_dx = 0.0;
    a8->line_dy = 0.0;
    a8->radius = 0.0;
    a8->radius2 = 0.0;
    a9[0] = 0.0;
    a9[1] = 0.0;
    a10[0] = 0.0;
    a10[1] = 0.0;
    *a11 = 0;

    if (a1->type != 1)
    {
        *a11 = 1;
        return;
    }
    Point2 c1v = {a1->center_x, a1->center_y};

    Point2 tp1 = {0.0, 0.0};
    Point2 tp2 = {0.0, 0.0};
    Point2 tp3 = {0.0, 0.0};
    Point2 tp4 = {0.0, 0.0};
    Point2 cl1 = {0.0, 0.0};
    Point2 cl2 = {0.0, 0.0};
    Point2 cl3 = {0.0, 0.0};
    Point2 cl4 = {0.0, 0.0};
    Vector2 seg_dir = {0.0, 0.0};
    double parms[2];
    int    dom[2];
    int    err = 0;
    int    count1 = 0;

    if (a2 == 0)
    {
        *a11 = 2;
        return;
    }
    Point2 c2v = {a2->center_x, a2->center_y};
    if (a2->type != 1)
    {
        *a11 = 2;
        return;
    }

    double r1  = a1->radius;
    double r2  = a2->radius;
    double d   = std::sqrt((c1v.x - c2v.x) * (c1v.x - c2v.x) +
                           (c1v.y - c2v.y) * (c1v.y - c2v.y));
    double tol0 = *a5;
    double rsum = r1 + r2;
    if (tol0 > d || rsum - tol0 > d)
    {
        *a11 = 3;
        return;
    }


    __m128d delta = _mm_set_pd(c2v.y - c1v.y, c2v.x - c1v.x);
    __m128d uvec  = _mm_mul_pd(_mm_set1_pd(1.0 / d), delta);
    double  ux    = _mm_cvtsd_f64(uvec);
    double  uy    = _mm_cvtsd_f64(_mm_unpackhi_pd(uvec, uvec));
    __m128d v64v  = uvec;
    if (!(r1 >= r2))
        v64v = _mm_xor_pd(v64v, _mm_set1_pd(-0.0));
    Point2 v64;
    _mm_storeu_pd(&v64.x, v64v);


    double perpX = -uy;
    double perpY = ux;
    seg_dir.x = perpX;
    seg_dir.y = perpY;
    if (dir1 == -1)
    {
        perpX = -perpX;
        perpY = -perpY;
        seg_dir.x = perpX;
        seg_dir.y = perpY;
    }

    if (tol0 + tol0 >= fabs(d - rsum))
    {

        if (r1 >= r2)
        {
            __m128d pv = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(r1), _mm_loadu_pd(&v64.x)),
                                    _mm_loadu_pd(&c1v.x));
            _mm_storeu_pd(&tp1.x, pv);
        }
        else
        {
            double t = -r2;
            __m128d pv = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t), _mm_loadu_pd(&v64.x)),
                                    _mm_loadu_pd(&c2v.x));
            _mm_storeu_pd(&tp3.x, pv);
        }

        int s1, s2;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, &tp1, a5, &cl1, a9, &s1, &err);
        if (a3 == 0)
            s1 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, &tp3, a5, &cl2, a9 + 1, &s2, &err);
        if (a4 == 0)
            s2 = -1;

        if (s1 == -1 && s2 == -1)
        {
            *a6 = 1;
            __m128d mid = _mm_mul_pd(_mm_set1_pd(0.5),
                                     _mm_set_pd(tp3.y + tp1.y, tp3.x + tp1.x));
            _mm_storeu_pd(&c2v.x, mid);
            ARC_SPLINE_cre_strt_seg_2d(&c2v, &c2v, &seg_dir, a7);
        }
    }
    else
    {

        seg_dir.x = 0.0;
        seg_dir.y = 0.0;

        Point2 P;
        if (tol0 >= fabs(r1 - r2))
        {
            double sx = c2v.x + c1v.x;
            double sy = c2v.y + c1v.y;
            __m128d pv = _mm_mul_pd(_mm_set1_pd(0.5), _mm_set_pd(sy, sx));
            _mm_storeu_pd(&P.x, pv);
        }
        else if (r1 > r2)
        {
            double t = -(r2 * d / rsum);
            __m128d pv = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t), _mm_loadu_pd(&v64.x)),
                                    _mm_loadu_pd(&c2v.x));
            _mm_storeu_pd(&P.x, pv);
        }
        else
        {
            double t = -(r1 * d / rsum);
            __m128d pv = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t), _mm_loadu_pd(&v64.x)),
                                    _mm_loadu_pd(&c1v.x));
            _mm_storeu_pd(&P.x, pv);
        }

        ARC_SPLINE_ask_tangents_thru_a_point_2d(a1, &P, a3, a5, &count1, &tp1,
                                                &tp2, parms, dom, &err);
        if (err > 0 || (a3 == 0 && count1 < 2))
        {
            *a11 = 4;
            return;
        }
        if ((tp1.y - tp2.y) * perpY + (tp1.x - tp2.x) * perpX < 0.0)
        {
            Point2 tmp = tp1;
            tp1 = tp2;
            tp2 = tmp;
        }

        ARC_SPLINE_ask_tangents_thru_a_point_2d(a2, &P, a4, a5, &count1, &tp3,
                                                &tp4, parms, dom, &err);
        if (err > 0 || (a4 == 0 && count1 < 2))
        {
            *a11 = 5;
            return;
        }
        if ((tp3.y - tp4.y) * perpY + (tp3.x - tp4.x) * perpX > 0.0)
        {
            Point2 tmp = tp3;
            tp3 = tp4;
            tp4 = tmp;
        }

        int s1, s2, s3, s4;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, &tp1, a5, &cl1, a9, &s1, &err);
        if (a3 == 0)
            s1 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, &tp3, a5, &cl2, a9 + 1, &s2, &err);
        if (a4 == 0)
            s2 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a1, &tp2, a5, &cl3, a10, &s3, &err);
        if (a3 == 0)
            s3 = -1;
        ARC_SPLINE_ask_parm_at_a_point_2d(a2, &tp4, a5, &cl4, a10 + 1, &s4, &err);
        if (a4 == 0)
            s4 = -1;

        if (s1 != 1 && s2 != 1)
        {
            ++*a6;
            ARC_SPLINE_cre_strt_seg_2d(&tp1, &tp3, &seg_dir, a7);
        }
        if (s3 != 1 && s4 != 1)
        {
            ++*a6;
            if (*a6 == 1)
            {
                ARC_SPLINE_cre_strt_seg_2d(&tp2, &tp4, &seg_dir, a7);
                a9[0] = a10[0];
                a9[1] = a10[1];
                return;
            }
            ARC_SPLINE_cre_strt_seg_2d(&tp2, &tp4, &seg_dir, a8);
        }
    }
}
