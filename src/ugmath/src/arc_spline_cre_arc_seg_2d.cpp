





















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
    int    type;
    int    dir;
    double base_x;
    double base_y;
    double start;
    double end;
    double mid_x;
    double mid_y;
    double dir_x;
    double dir_y;
    double parm;
    double radius;
};



void h053(const double* y, const double* x, double* angle);

#include <math.h>
#include <emmintrin.h>


static const double UBARC_ARCSEG_K_DEG2RAD = 0.01745329251994328;

void ARC_SPLINE_cre_arc_seg_2d(const UGS::Math::Point2* pt,
                               const UGS::Math::Vector2* tan,
                               double sweep,
                               double radius,
                               int sense,
                               struct ARC_SPLINE_1_seg_2d_s* seg,
                               UGS::Math::Point2* end_pt,
                               UGS::Math::Vector2* end_tan)
{
    double vx = tan->x;
    double vy = tan->y;
    __m128i sense4 = _mm_set1_epi32(sense);
    __m128d rr     = _mm_set1_pd(radius);
    __m128d center = _mm_setzero_pd();
    double  vx_ = vx;
    double  vy_ = vy;
    double  incl;
    h053(&vy_, &vx_, &incl);
    double angle0 = incl * 57.29577951308235;
    double angle1 = (double)sense * sweep + angle0;

    if (sense == -1)
    {
        double s = sin(sweep * UBARC_ARCSEG_K_DEG2RAD) * radius;
        double c = cos(sweep * UBARC_ARCSEG_K_DEG2RAD) * radius - radius;
        end_pt->x = s * vx + pt->x - c * vy;
        end_pt->y = s * vy + pt->y + c * vx;
    }
    else if (sense == 1)
    {
        double s = sin(sweep * UBARC_ARCSEG_K_DEG2RAD) * radius;
        double c = radius - cos(sweep * UBARC_ARCSEG_K_DEG2RAD) * radius;
        end_pt->x = s * vx + pt->x - c * vy;
        end_pt->y = s * vy + pt->y + c * vx;
    }
    else
    {
        end_pt->x = pt->x;
        end_pt->y = pt->y;
    }

    double end_rad = angle1 * UBARC_ARCSEG_K_DEG2RAD;
    end_tan->x = cos(end_rad);
    end_tan->y = sin(end_rad);

    UGS::Math::Vector2 normal;
    normal.x = -vy;
    normal.y = vx;
    if (sense)
    {
        center = _mm_add_pd(
            _mm_mul_pd(_mm_mul_pd(_mm_cvtepi32_pd(_mm_move_epi64(sense4)), rr),
                       _mm_loadu_pd(&normal.x)),
            _mm_loadu_pd(&pt->x));
    }

    seg->type   = 1;
    seg->dir    = sense;
    seg->base_x = pt->x;
    seg->base_y = pt->y;
    seg->start  = angle0;
    seg->end    = angle1;
    _mm_store_sd(&seg->mid_x, center);
    _mm_store_sd(&seg->mid_y, _mm_unpackhi_pd(center, center));
    seg->dir_x  = 0.0;
    seg->dir_y  = 0.0;
    seg->parm   = radius;
    seg->radius = radius;
}
