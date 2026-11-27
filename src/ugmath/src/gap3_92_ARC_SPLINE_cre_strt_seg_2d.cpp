











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
    double strt_x;
    double strt_y;
    double start;
    double end;
    double mid_x;
    double mid_y;
    double dir_x;
    double dir_y;
    double parm;
    double radius;
};



int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);

void h053(const double* y, const double* x, double* angle);

#include <math.h>
#include <emmintrin.h>








extern const double g_math_half2[2];

void ARC_SPLINE_cre_strt_seg_2d(const UGS::Math::Point2* a1,
                                const UGS::Math::Point2* a2,
                                const UGS::Math::Vector2* a3,
                                struct ARC_SPLINE_1_seg_2d_s* a4)
{
    double len_out;
    UGS::Math::Vector2 v;
    UGS::Math::Point2  base;
    double len = sqrt((a1->x - a2->x) * (a1->x - a2->x) +
                      (a1->y - a2->y) * (a1->y - a2->y));
    if ( len >= 1.0e-10 )
    {
        v.x = a2->x - a1->x;
        v.y = a2->y - a1->y;
        VEC2_unitize(&v, 1.0e-10, &len_out, &v);
        base = *a2;
    }
    else
    {
        v.x  = a3->x;
        v.y  = a3->y;
        base = *a1;
        len  = 0.0;
    }
    double vx = v.x;
    double vy = v.y;
    double angle;
    h053(&vy, &vx, &angle);
    double deg = angle * 57.29577951308235;
    a4->type    = 0;
    a4->nsegs   = 0;
    a4->strt_x  = a1->x;
    a4->strt_y  = a1->y;
    a4->start   = deg;
    a4->end     = deg;
    double mx = base.x + a1->x;
    double my = base.y + a1->y;
    __m128d sum = _mm_set_pd(my, mx);
    __m128d halfv = _mm_load_pd(g_math_half2);
    __m128d midv = _mm_mul_pd(halfv, sum);
    _mm_store_sd(&a4->mid_x, midv);
    _mm_store_sd(&a4->mid_y, _mm_unpackhi_pd(midv, midv));
    a4->dir_x   = v.x;
    a4->dir_y   = v.y;
    a4->parm    = len;
    a4->radius  = len;
}
