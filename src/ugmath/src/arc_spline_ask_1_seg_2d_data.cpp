









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
    double dir_x;
    double dir_y;
    double radius;
};

namespace UGS { namespace Math {
struct alignas(16) Point2  { double x; double y; };
struct alignas(16) Vector2 { double x; double y; };
}}

using UGS::Math::Point2;
using UGS::Math::Vector2;


static const double UBARC_K_DEG2RAD = 0.01745329251994328;



void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within,
                                    double t, Point2* pt, Vector2* tan_out, int* status);

void ARC_SPLINE_inter_line_line_2d(const double* const tol, const Point2* p0,
                                   const Point2* p1, int homodromic, Vector2* u,
                                   Vector2* v, Point2* inter, double* out8, double* out9,
                                   int* status);

void ARC_SPLINE_ask_1_seg_2d_data(const ARC_SPLINE_1_seg_2d_s* seg, int flag,
                                  int* type_out, int* dir_out, double* angles_out,
                                  double* len_out, double* curv_out, Point2* center_out,
                                  Point2* base_out, Vector2* start_tan, Point2* end_pt,
                                  Vector2* end_tan, Point2* inter_pt, int* status)
{
    *type_out = -1;
    *len_out  = 0.0;
    *curv_out = 0.0;
    *status   = 0;
    if (!seg)
        return;

    *type_out = seg->type;
    *dir_out  = seg->dir;

    double end   = seg->end;
    double start = seg->start;
    double range = (end - start) * (double)seg->dir;
    if (range < 0.0)
    {
        range = range + 360.0;
        end   = (double)seg->dir * range + start;
    }
    angles_out[0] = start;
    angles_out[1] = end;

    base_out->x   = seg->base_x;
    base_out->y   = seg->base_y;
    center_out->x = seg->center_x;
    center_out->y = seg->center_y;

    if (seg->type == 0)
    {
        start_tan->x = seg->dir_x;
        start_tan->y = seg->dir_y;
        double len   = seg->radius;
        *len_out     = len;
        __m128d endv = _mm_mul_pd(_mm_set1_pd(len), _mm_loadu_pd(&start_tan->x));
        _mm_storeu_pd(&end_pt->x, _mm_add_pd(endv, _mm_loadu_pd(&base_out->x)));
        end_tan->x  = start_tan->x;
        end_tan->y  = start_tan->y;
        inter_pt->x = center_out->x;
        inter_pt->y = center_out->y;
    }
    else if (seg->type == 1)
    {
        double radius = seg->radius;
        if (1.0e-10 > radius)
        {
            *status = 1;
        }
        else
        {
            *len_out  = radius * UBARC_K_DEG2RAD * range;
            *curv_out = 1.0 / radius;
            double ang = start * UBARC_K_DEG2RAD;
            start_tan->x = cos(ang);
            start_tan->y = sin(ang);
            ARC_SPLINE_evaluate_arc_seg_2d(seg, 1, end, end_pt, end_tan, status);
            if (flag == 1)
            {
                const double tol[2] = { 1.0e-10, 0.005 };
                double d8[2];
                double d9;
                int    st = 0;
                ARC_SPLINE_inter_line_line_2d(tol, base_out, end_pt, flag, start_tan,
                                              end_tan, inter_pt, d8, &d9, &st);
                if (st == 1)
                    *status = 2;
            }
        }
    }
    else
    {
        *status = 3;
    }
}
