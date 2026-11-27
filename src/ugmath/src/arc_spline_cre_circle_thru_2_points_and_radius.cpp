













#include <cmath>
#include <intrin.h>

namespace UGS
{
namespace Math
{
struct alignas(16) Point2
{
    double x;
    double y;
};
struct alignas(16) Vector2
{
    double x;
    double y;
};
}
}


struct ARC_SPLINE_1_seg_2d_s
{
    long long q[11];
};
static_assert(sizeof(ARC_SPLINE_1_seg_2d_s) == 0x58, "seg layout");

using UGS::Math::Point2;
using UGS::Math::Vector2;



void __cdecl ARC_SPLINE_cre_arc_seg_2d(const Point2* p_start, const Vector2* tan_unit,
                                       double sweep_deg, double radius, int orient,
                                       ARC_SPLINE_1_seg_2d_s* seg, Point2* out_end_pt,
                                       Vector2* out_end_dir);

static inline __m128d v2_make(double x, double y)
{
    return _mm_set_pd(y, x);
}

static inline double v2_lo(__m128d v)
{
    return _mm_cvtsd_f64(v);
}

static inline double v2_hi(__m128d v)
{
    return _mm_cvtsd_f64(_mm_unpackhi_pd(v, v));
}

void __cdecl ARC_SPLINE_cre_circle_thru_2_points_and_radius(
    const Point2* a1,
    const Point2* a2,
    double a3,
    int a4,
    const double* const a5,
    int* a6,
    ARC_SPLINE_1_seg_2d_s* a7,
    ARC_SPLINE_1_seg_2d_s* a8,
    int* a9)
{
    ARC_SPLINE_1_seg_2d_s* const seg1 = a7;
    ARC_SPLINE_1_seg_2d_s* const seg2 = a8;
    *a6 = 0;
    for (int i = 0; i < 11; ++i)
        ((long long*)seg1)[i] = 0;
    for (int i = 0; i < 11; ++i)
        ((long long*)seg2)[i] = 0;
    *a9 = 0;

    const double y1 = a1->y;
    const double x1 = a1->x;
    const double y2 = a2->y;
    const double x2 = a2->x;

    const double dy   = y1 - y2;
    const double dx   = x1 - x2;
    const double dist = sqrt(dy * dy + dx * dx);
    const double half = dist * 0.5;

    if (a5[0] >= half)
    {
        *a9 = 1;
    }
    else
    {
        const __m128d vsign = _mm_set1_pd(-0.0);
        const __m128d vr    = _mm_set1_pd(a3);


        const __m128d vmid = _mm_mul_pd(v2_make(x2 + x1, y2 + y1), _mm_set1_pd(0.5));
        Vector2       mid;
        mid.x = v2_lo(vmid);
        mid.y = v2_hi(vmid);


        __m128d vdir = v2_make(x2 - x1, y2 - y1);
        Vector2 dir;
        _mm_storeu_pd(&dir.x, vdir);
        const __m128d vu = _mm_mul_pd(vdir, _mm_set1_pd(0.5 / half));
        dir.x = v2_lo(vu);
        dir.y = v2_hi(vu);
        Vector2 nrm;
        nrm.y = dir.x;
        nrm.x = -dir.y;

        if (a5[0] >= fabs(a3 - half))
        {


            *a6 = 1;
            dir.x = dir.y;
            dir.y = -nrm.y;
            Point2 ep;
            ARC_SPLINE_cre_arc_seg_2d(a1, &dir, 360.0, half, 1, a7, &ep, &mid);
        }
        else
        {

            if (!(a3 > half))
                return;
            *a6 = 2;

            const double invr = 1.0 / a3;
            Point2       ep;


            __m128d      vc1  = _mm_add_pd(vmid, _mm_set_pd(dir.x * a3, nrm.x * a3));
            __m128d      vuu1 = _mm_mul_pd(v2_make(a1->x - v2_lo(vc1), a1->y - v2_hi(vc1)),
                                           _mm_set1_pd(invr));
            int o1 = (a4 == 1) ? -1 : 1;
            if (a4 == 1)
            {
                dir.x = v2_hi(vuu1);
                dir.y = -v2_lo(vuu1);
            }
            else
            {
                dir.x = -v2_hi(vuu1);
                dir.y = v2_lo(vuu1);
            }
            ARC_SPLINE_cre_arc_seg_2d(a1, &dir, 360.0, a3, o1, a7, &ep, &mid);


            __m128d vc2  = _mm_add_pd(vmid, _mm_mul_pd(_mm_set1_pd(-a3),
                                                       _mm_loadu_pd(&nrm.x)));
            __m128d vuu2 = _mm_mul_pd(v2_make(a1->x - v2_lo(vc2), a1->y - v2_hi(vc2)),
                                      _mm_set1_pd(invr));
            int o2 = (a4 == 0) ? -1 : 1;
            if (a4 == 0)
            {
                dir.x = v2_hi(vuu2);
                dir.y = -v2_lo(vuu2);
            }
            else
            {
                dir.x = -v2_hi(vuu2);
                dir.y = v2_lo(vuu2);
            }
            ARC_SPLINE_cre_arc_seg_2d(a1, &dir, 360.0, a3, o2, a8, &ep, &mid);
        }
    }
}
