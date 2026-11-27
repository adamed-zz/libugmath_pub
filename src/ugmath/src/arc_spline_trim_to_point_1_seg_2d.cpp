










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
    int    type;
    int    nsegs;
    double base_x;
    double base_y;
    double start;
    double end;
    double mid_x;
    double mid_y;
    double dir_x;
    double dir_y;
    double radius;
    double parm;
};


void ARC_SPLINE_evaluate_arc_seg_2d(const ARC_SPLINE_1_seg_2d_s* seg, int within, double t,
                                    UGS::Math::Point2* pt, UGS::Math::Vector2* tan_out,
                                    int* status);
double ARC_SPLINE_ask_dist_pt_to_1_seg_2d(ARC_SPLINE_1_seg_2d_s* seg, UGS::Math::Point2* pt,
                                          int within, double* dist, UGS::Math::Point2* closest,
                                          double* param, int* side, int* status);
void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2* a1, const UGS::Math::Point2* a2,
                                const UGS::Math::Vector2* a3, ARC_SPLINE_1_seg_2d_s* a4);
void ARC_SPLINE_cre_circle_from_chord_end_data_2d(const UGS::Math::Point2* p1,
                                                  const UGS::Math::Vector2* v1,
                                                  const UGS::Math::Point2* p2,
                                                  const UGS::Math::Vector2* v2, int dir,
                                                  double* radius, ARC_SPLINE_1_seg_2d_s* seg,
                                                  int* status);


static const double TRIM_K_DEG2RAD = 0.01745329251994328;


static __forceinline void trim_clear_seg(ARC_SPLINE_1_seg_2d_s* a)
{
    unsigned long long* p = reinterpret_cast<unsigned long long*>(a);
    p[0]  = 0;
    p[1]  = 0;
    p[2]  = 0;
    p[3]  = 0;
    p[4]  = 0;
    p[5]  = 0;
    p[6]  = 0;
    p[7]  = 0;
    p[8]  = 0;
    p[9]  = 0;
    p[10] = 0;
}

void ARC_SPLINE_trim_to_point_1_seg_2d(UGS::Math::Point2* a1, double* a2,
                                       ARC_SPLINE_1_seg_2d_s* a3, int* a4)
{
    *a4 = 0;
    int status = 0;
    int type   = -1;
    int nsegs;



    struct __declspec(align(8)) TRIM_LOCALS
    {
        UGS::Math::Vector2 tmp_v;
        UGS::Math::Point2  point;
        UGS::Math::Vector2 tan_start;
        UGS::Math::Point2  base;
        UGS::Math::Vector2 tan_pt;
        UGS::Math::Point2  tmp_pt;
    };
    __declspec(align(8)) TRIM_LOCALS L;
    double radius;

    L.base      = {0.0, 0.0};
    L.point     = {0.0, 0.0};
    L.tan_start = {0.0, 0.0};
    L.tan_pt    = {0.0, 0.0};

    if ( a3 )
    {
        nsegs        = a3->nsegs;
        double end   = a3->end;
        double start = a3->start;
        type         = a3->type;
        double span  = (end - start) * (double)nsegs;
        if ( span < 0.0 )
            end = (span + 360.0) * (double)nsegs + start;
        L.base.x = a3->base_x;
        L.base.y = a3->base_y;
        if ( type == 0 )
        {
            L.tan_start.x = a3->dir_x;
            L.tan_start.y = a3->dir_y;
        }
        else if ( type == 1 )
        {
            if ( a3->radius < 1.0e-10 )
            {
                status = 1;
            }
            else
            {
                double ang    = start * TRIM_K_DEG2RAD;
                L.tan_start.x = cos(ang);
                L.tan_start.y = sin(ang);
                ARC_SPLINE_evaluate_arc_seg_2d(a3, 1, end, &L.tmp_pt, &L.tmp_v, &status);
            }
        }
        else
        {
            status = 3;
        }
    }
    else
    {
        nsegs = *(volatile int*)&status;
    }

    ARC_SPLINE_ask_dist_pt_to_1_seg_2d(a3, a1, 0, a2, &L.point, &L.tmp_v.x, (int*)&radius,
                                       &status);
    if ( status > 0 )
    {
        *a4 = 1;
        return;
    }

    double t = L.tmp_v.x;
    if ( a3->type == 0 )
    {
        L.tan_pt.x = a3->dir_x;
        L.tan_pt.y = a3->dir_y;
        status     = 0;
        L.point.x  = L.tan_pt.x * t + a3->base_x;
        L.point.y  = L.tan_pt.y * t + a3->base_y;
    }
    else
    {
        ARC_SPLINE_evaluate_arc_seg_2d(a3, 1, t, &L.point, &L.tan_pt, &status);
        if ( status > 0 )
        {
            *a4 = 2;
            return;
        }
    }

    if ( type == 0 )
    {
        trim_clear_seg(a3);
        if ( t >= 0.0 )
        {
            ARC_SPLINE_cre_strt_seg_2d(&L.base, &L.point, &L.tan_start, a3);
            return;
        }
        __m128 nv = _mm_xor_ps(_mm_castpd_ps(_mm_loadu_pd(&L.tan_start.x)),
                               _mm_castsi128_ps(_mm_set1_epi64x((long long)0x8000000000000000ULL)));
        _mm_store_sd(&L.tan_pt.x, _mm_castps_pd(nv));
        _mm_store_sd(&L.tan_pt.y, _mm_unpackhi_pd(_mm_castps_pd(nv), _mm_castps_pd(nv)));
        ARC_SPLINE_cre_strt_seg_2d(&L.base, &L.point, &L.tan_pt, a3);
        return;
    }
    else if ( type == 1 )
    {
        trim_clear_seg(a3);
        radius = -1.0;
        ARC_SPLINE_cre_circle_from_chord_end_data_2d(&L.base, &L.tan_start, &L.point, &L.tan_pt,
                                                     nsegs, &radius, a3, &status);
        if ( status > 0 )
            *a4 = 3;
    }
}
