









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
    double u28;
    double u30;
    double dir_x;
    double dir_y;
    double radius;
};

namespace UGS { namespace Math {
struct Point2  { double x; double y; };
struct Vector2 { double x; double y; };
}}


static const double UBARC_K_DEG2RAD = 0.01745329251994328;


void ARC_SPLINE_evaluate_arc_seg_2d(
    const ARC_SPLINE_1_seg_2d_s* seg,
    int within,
    double t,
    UGS::Math::Point2* pt,
    UGS::Math::Vector2* tan_out,
    int* status);

void ARC_SPLINE_ask_end_pts_of_1_seg_2d(
    ARC_SPLINE_1_seg_2d_s* seg,
    UGS::Math::Point2* start_pt,
    UGS::Math::Vector2* start_tan,
    UGS::Math::Point2* end_pt,
    UGS::Math::Vector2* end_tan,
    int* status)
{
    *status = 0;
    if (!seg)
    {
        *status = 1;
        return;
    }

    start_pt->x = seg->base_x;
    start_pt->y = seg->base_y;

    int tag = seg->type;
    if (tag == 0)
    {
        start_tan->x = seg->dir_x;
        start_tan->y = seg->dir_y;
        _mm_storeu_pd(&end_pt->x,
                      _mm_add_pd(_mm_loadu_pd(&start_pt->x),
                                 _mm_set_pd(start_tan->y * seg->radius,
                                            start_tan->x * seg->radius)));
        end_tan->x = start_tan->x;
        end_tan->y = start_tan->y;
    }
    else if (tag == 1)
    {
        double start = seg->start;
        double end = seg->end;
        if (1e-10 > seg->radius)
        {
            *status = 2;
        }
        else
        {
            double ang = start * UBARC_K_DEG2RAD;
            start_tan->x = cos(ang);
            start_tan->y = sin(ang);
            ARC_SPLINE_evaluate_arc_seg_2d(seg, 1, end, end_pt, end_tan, status);
        }
    }
    else
    {
        *status = 3;
    }
}
