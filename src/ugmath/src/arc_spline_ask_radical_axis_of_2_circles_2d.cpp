
























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
    int    kind;
    int    dir;
    double p0x;
    double p0y;
    double ang0;
    double ang1;
    double cx;
    double cy;
    double d0;
    double d1;
    double radius;
};


int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);


void ARC_SPLINE_ask_radical_axis_of_2_circles_2d(
    const ARC_SPLINE_1_seg_2d_s* seg1, const ARC_SPLINE_1_seg_2d_s* seg2,
    UGS::Math::Point2* axis_pt, UGS::Math::Vector2* axis_dir,
    int* status, int* err);


#include <math.h>
#include <emmintrin.h>


void ARC_SPLINE_ask_radical_axis_of_2_circles_2d(
    const ARC_SPLINE_1_seg_2d_s* seg1, const ARC_SPLINE_1_seg_2d_s* seg2,
    UGS::Math::Point2* axis_pt, UGS::Math::Vector2* axis_dir,
    int* status, int* err)
{
    axis_pt->x = 0.0;
    axis_pt->y = 0.0;
    axis_dir->x = 0.0;
    axis_dir->y = 0.0;
    *status = 2;
    *err = 0;

    if (!seg1)
    {
        *err = 1;
        return;
    }
    const double c1x = seg1->cx;
    const double c1y = seg1->cy;
    if (seg1->kind != 1)
    {
        *err = 1;
        return;
    }
    const double r1 = seg1->radius;

    if (!seg2)
    {
        *err = 2;
        return;
    }
    const double c2x = seg2->cx;
    const double c2y = seg2->cy;
    if (seg2->kind != 1)
    {
        *err = 2;
        return;
    }
    const double r2 = seg2->radius;

    UGS::Math::Vector2 v;
    v.y = c2y - c1y;
    v.x = c2x - c1x;
    const double sum = _mm_cvtsd_f64(
        _mm_add_sd(_mm_set_sd(r1), _mm_set_sd(r2)));

    double len;
    VEC2_unitize(&v, 1.0e-10, &len, &v);

    if (1.0e-10 > len)
    {
        *status = 3;
    }
    else
    {
        const __m128d sign = _mm_set1_pd(-0.0);
        if (r2 > r1)
        {
            __m128d vv = _mm_loadu_pd(&v.x);
            vv = _mm_castps_pd(_mm_xor_ps(_mm_castpd_ps(vv), _mm_castpd_ps(sign)));
            v.x = _mm_cvtsd_f64(vv);
            v.y = _mm_cvtsd_f64(_mm_unpackhi_pd(vv, vv));
        }
        axis_dir->y = v.x;
        axis_dir->x = _mm_cvtsd_f64(_mm_castps_pd(
            _mm_xor_ps(_mm_castpd_ps(_mm_set_sd(v.y)), _mm_castpd_ps(sign))));

        if (1.0e-10 >= fabs(r1 - r2))
        {

            const __m128d sums = _mm_unpacklo_pd(_mm_set_sd(c2x + c1x),
                                                 _mm_set_sd(c2y + c1y));
            __m128d mid = _mm_mul_pd(_mm_set1_pd(0.5), sums);
            _mm_storeu_pd(&axis_pt->x, mid);
            if (1.0e-10 >= fabs(sum - len))
            {
                *status = 1;
            }
            else
            {
                *status = (len > sum) ? 0 : 2;
            }
        }
        else
        {

            *status = (len > sum) ? 0 : 2;
            double rmin = r1;
            double rmax = r2;
            if (r1 > r2)
            {
                rmin = r2;
                rmax = r1;
            }
            const __m128d sums = _mm_unpacklo_pd(_mm_set_sd(c2x + c1x),
                                                 _mm_set_sd(c2y + c1y));
            __m128d mid = _mm_mul_pd(_mm_set1_pd(0.5), sums);
            const double t = (rmax * rmax - rmin * rmin) * 0.5 / len;
            const __m128d um = _mm_loadu_pd(&v.x);
            __m128d prod = _mm_mul_pd(_mm_set1_pd(t), um);
            const __m128d midhi = _mm_unpackhi_pd(mid, mid);
            __m128d repack = _mm_unpacklo_pd(mid, midhi);
            repack = _mm_add_pd(prod, repack);
            _mm_storeu_pd(&axis_pt->x, repack);
        }
    }
}
