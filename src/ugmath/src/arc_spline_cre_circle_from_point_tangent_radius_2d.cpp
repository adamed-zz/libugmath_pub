














#include <cstring>
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



void h053(const double* a1, const double* a2, double* a3);

void ARC_SPLINE_cre_circle_from_point_tangent_radius_2d(
    const UGS::Math::Point2*  point,
    const UGS::Math::Vector2* tangent,
    double                    radius,
    int                       sense,
    ARC_SPLINE_1_seg_2d_s*    seg)
{

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


    const __m128i dir_b = _mm_set1_epi32(sense);
    const __m128d rr    = _mm_set1_pd(radius);


    double tan_x = tangent->x;
    double tan_y = tangent->y;
    double angle_rad;
    h053(&tan_y, &tan_x, &angle_rad);

    const double angle_deg = angle_rad * 57.29577951308235;


    UGS::Math::Vector2 normal;
    normal.x = -tangent->y;
    normal.y = tangent->x;

    const double angle_end = (sense == -1) ? angle_deg - 360.0 : angle_deg + 360.0;



    const __m128d ppt = _mm_loadu_pd(&point->x);

    seg->tag      = 1;
    seg->sense    = sense;
    seg->base_x   = point->x;
    seg->base_y   = point->y;
    seg->start    = angle_deg;
    seg->end      = angle_end;



    const __m128d center = _mm_add_pd(
        _mm_mul_pd(_mm_mul_pd(_mm_cvtepi32_pd(_mm_move_epi64(dir_b)), rr), _mm_loadu_pd(&normal.x)),
        ppt);
    seg->center_x = _mm_cvtsd_f64(center);
    seg->center_y = _mm_cvtsd_f64(_mm_unpackhi_pd(center, center));

    seg->d38     = 0.0;
    seg->d40     = 0.0;
    seg->radius1 = radius;
    seg->radius2 = radius;
}
