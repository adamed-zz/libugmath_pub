















#include <math.h>
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



double ARC_SPLINE_ask_dist_pt_to_line_2d(const UGS::Math::Point2*  pt,
                                         const UGS::Math::Point2*  origin,
                                         const UGS::Math::Vector2* dir,
                                         double                    tol,
                                         UGS::Math::Point2*        closest,
                                         double*                   parm,
                                         int*                      side);

void ARC_SPLINE_inter_line_line_2d(const double* const       tol,
                                   const UGS::Math::Point2*  p1,
                                   const UGS::Math::Point2*  p2,
                                   int                       unitized,
                                   UGS::Math::Vector2*       dir1,
                                   UGS::Math::Vector2*       dir2,
                                   UGS::Math::Point2*        out_pt,
                                   double*                   params,
                                   double*                   dot,
                                   int*                      status);

void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(const UGS::Math::Point2*  point,
                                                        const UGS::Math::Vector2* tangent,
                                                        double                    radius,
                                                        int                       sense,
                                                        ARC_SPLINE_1_seg_2d_s*    seg);

void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2*  p1,
                                const UGS::Math::Point2*  p2,
                                const UGS::Math::Vector2* fallback_dir,
                                ARC_SPLINE_1_seg_2d_s*    seg);

void ARC_SPLINE_cre_circle_thru_pt_and_tangent_to_line_at_pt_2d(
    const UGS::Math::Point2*  a1,
    const UGS::Math::Vector2* a2,
    const UGS::Math::Point2*  a3,
    const double* const       a4,
    ARC_SPLINE_1_seg_2d_s*    a5,
    int*                      a6)
{



    ARC_SPLINE_1_seg_2d_s* const seg    = a5;
    int* const                   status = a6;

    UGS::Math::Point2 closest = {0.0, 0.0};


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
    *status = 0;


    const UGS::Math::Point2 p3 = *a3;
    double dist = sqrt((a1->x - p3.x) * (a1->x - p3.x) +
                       (a1->y - p3.y) * (a1->y - p3.y));

    if (*a4 >= dist)
    {

        seg->tag      = -1;
        seg->sense    = 1;
        seg->base_x   = a1->x;
        seg->base_y   = a1->y;
        seg->start    = 90.0;
        seg->end      = 450.0;
        seg->center_x = a1->x;
        seg->center_y = a1->y;
        seg->d38      = 0.0;
        seg->d40      = 0.0;
        seg->radius1  = 0.0;
        seg->radius2  = 0.0;
        *status = 1;
        return;
    }


    UGS::Math::Vector2 chord;
    const __m128d      delta = _mm_unpacklo_pd(_mm_set_sd(p3.x - a1->x),
                                               _mm_set_sd(p3.y - a1->y));
    _mm_storeu_pd(&chord.x, delta);
    const __m128d scaled = _mm_mul_pd(_mm_set1_pd(1.0 / dist), delta);
    chord.x              = _mm_cvtsd_f64(scaled);
    chord.y              = _mm_cvtsd_f64(_mm_unpackhi_pd(scaled, scaled));

    ARC_SPLINE_ask_dist_pt_to_line_2d(a3, a1, a2, *a4, &closest, (double*)&a6, (int*)&a5);
    const int side = *(int*)&a5;

    if (side != 0)
    {

        const __m128d sum = _mm_unpacklo_pd(_mm_set_sd(p3.x + a1->x),
                                            _mm_set_sd(p3.y + a1->y));
        const __m128d midv = _mm_mul_pd(_mm_set_pd(0.5, 0.5), sum);
        closest.x          = _mm_cvtsd_f64(midv);
        closest.y          = _mm_cvtsd_f64(_mm_unpackhi_pd(midv, midv));

        UGS::Math::Vector2 chord_normal;
        chord_normal.x = -chord.y;
        chord_normal.y = chord.x;

        UGS::Math::Vector2 tan_normal;
        tan_normal.x = -a2->y;
        tan_normal.y = a2->x;

        UGS::Math::Point2 out_pt;
        double            params[2];
        ARC_SPLINE_inter_line_line_2d(a4, &closest, a1, 1, &chord_normal, &tan_normal,
                                      &out_pt, params, (double*)&a6, (int*)&a5);

        if (*(int*)&a5 == 0)
        {
            double radius = fabs(params[1]);
            int    sense  = (side == 1) ? -1 : 1;
            ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(a1, a2, radius, sense, seg);
            return;
        }
    }

    ARC_SPLINE_cre_strt_seg_2d(a1, a3, &chord, seg);
    *status = 2;
}
