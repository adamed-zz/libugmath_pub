


























#include <cmath>
#include <emmintrin.h>

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




void ARC_SPLINE_inter_line_line_2d(
    const double* const       tol,
    const UGS::Math::Point2*  p1,
    const UGS::Math::Point2*  p2,
    int                       unitized,
    UGS::Math::Vector2*       dir1,
    UGS::Math::Vector2*       dir2,
    UGS::Math::Point2*        out_pt,
    double*                   parms,
    double*                   dot,
    int*                      status);

double ARC_SPLINE_ask_dist_pt_to_line_2d(
    const UGS::Math::Point2*  pt,
    const UGS::Math::Point2*  origin,
    const UGS::Math::Vector2* dir,
    double                    tol,
    UGS::Math::Point2*        closest,
    double*                   t,
    int*                      side);

void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(
    const UGS::Math::Point2*  point,
    const UGS::Math::Vector2* tangent,
    double                    radius,
    int                       sense,
    ARC_SPLINE_1_seg_2d_s*    seg);

void ARC_SPLINE_cre_circle_from_chord_end_data_2d(
    const UGS::Math::Point2*  p1,
    const UGS::Math::Vector2* v1,
    const UGS::Math::Point2*  p2,
    const UGS::Math::Vector2* v2,
    int                       sense,
    double*                   param,
    ARC_SPLINE_1_seg_2d_s*    seg,
    int*                      status);

void ARC_SPLINE_cre_circle_tangent_to_line_and_line_at_pt_2d(
    UGS::Math::Point2*        pt1,
    UGS::Math::Vector2*       dir1,
    UGS::Math::Point2*        pt2,
    UGS::Math::Vector2*       dir2,
    int                       flag,
    double*                   tol,
    ARC_SPLINE_1_seg_2d_s*    seg,
    UGS::Math::Point2*        out_pt,
    UGS::Math::Vector2*       out_vec,
    int*                      ifail)
{


    UGS::Math::Point2* const opt = out_pt;
    int* const               stp = ifail;

    opt->x = 0.0;
    opt->y = 0.0;
    *stp   = 0;
    UGS::Math::Point2 xpt;
    xpt.x = 0.0;
    xpt.y = 0.0;
    if (seg == 0)
    {
        *stp = 1;
        return;
    }


    seg->tag      = 0;
    seg->sense    = 0;
    seg->base_x   = 0.0;
    seg->base_y   = 0.0;
    seg->start    = 0.0;
    seg->end      = 0.0;
    seg->center_x = 0.0;
    seg->center_y = 0.0;
    seg->d38      = 0.0;
    seg->d40      = 0.0;
    seg->radius1  = 0.0;
    seg->radius2  = 0.0;

    double parm[2];
    ARC_SPLINE_inter_line_line_2d(tol, pt1, pt2, 1, dir1, dir2, &xpt, parm,
                                  (double *)&ifail, (int *)&out_pt);
    if (*(int *)&out_pt > 1)
    {
        *stp = 2;
        return;
    }
    if (*(int *)&out_pt == 1)
    {

        out_vec->x = dir1->x;
        out_vec->y = dir1->y;
        const double radius = ARC_SPLINE_ask_dist_pt_to_line_2d(
                                  pt1, pt2, out_vec, *tol, opt, (double *)&ifail,
                                  (int *)&out_pt)
                              * 0.5;
        if (*(int *)&out_pt == -1)
        {
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(pt1, dir1, radius, -1, seg);
        }
        else if (*(int *)&out_pt == 1)
        {
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(opt, out_vec, radius, -1, seg);
        }
        else
        {
            *stp = 1;
        }
        return;
    }


    const double d2x = dir2->x;
    const double d2y = dir2->y;
    out_vec->x = d2x;
    out_vec->y = d2y;
    double dist = sqrt((xpt.x - pt1->x) * (xpt.x - pt1->x)
                       + (xpt.y - pt1->y) * (xpt.y - pt1->y));
    if (*tol > dist)
    {
        *stp = 3;
        return;
    }

    int sense = 1;
    if (flag != 108)
        sense = -1;
    const double cross = d2y * dir1->x - d2x * dir1->y;

    int s1;
    if (1e-10 >= fabs(parm[0] - 0.0))
        s1 = 0;
    else
        s1 = (parm[0] > 0.0) ? 1 : -1;

    int s2 = 0;
    if (!(1e-10 >= fabs(cross - 0.0)))
        s2 = (cross > 0.0) ? sense : -sense;

    const __m128d sign = _mm_set1_pd(-0.0);
    if (s1 * s2 < 0)
    {
        __m128d v = _mm_loadu_pd(&out_vec->x);
        _mm_storeu_pd(&out_vec->x, _mm_xor_pd(v, sign));
    }
    if (s1 != 1)
        dist = -dist;

    const __m128d c = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(dist), _mm_loadu_pd(&out_vec->x)),
                                 _mm_loadu_pd(&xpt.x));
    _mm_storeu_pd(&opt->x, c);

    *(double *)&ifail = -1.0;
    ARC_SPLINE_cre_circle_from_chord_end_data_2d(pt1, dir1, opt, out_vec, sense,
                                                 (double *)&ifail, seg, (int *)&out_pt);
    if (*(int *)&out_pt > 0)
        *stp = 4;
}
