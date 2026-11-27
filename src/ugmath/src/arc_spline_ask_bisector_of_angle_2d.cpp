










#include <cmath>
#include <emmintrin.h>

namespace UGS {
namespace Math {

struct Point2 {
    double x;
    double y;
};

struct Vector2 {
    double x;
    double y;
};

}
}

using UGS::Math::Point2;
using UGS::Math::Vector2;



void ARC_SPLINE_ask_isosceles_to_pt_2d(const double* a1, Point2* a2,
                                       Vector2* a3, Point2* a4, Vector2* a5,
                                       int a6, Point2* a7, double* a8, int* a9,
                                       Point2* a10, Point2* a11, int* a12,
                                       int* a13);


int __declspec(noinline) VEC2_unitize(const Vector2* v, double tol, double* len,
                                      Vector2* out);

void ARC_SPLINE_ask_bisector_of_angle_2d(double* a1, Point2* a2, Vector2* a3,
                                         Point2* a4, Vector2* a5, int a6,
                                         Point2* a7, double* a8, int* a9,
                                         Point2* a10, Vector2* a11)
{
    Point2 v30 = {0.0, 0.0};
    Point2 v31;
    int st12;
    int st13;

    a10->x = 0.0;
    a10->y = 0.0;
    a11->x = 0.0;
    a11->y = 0.0;

    ARC_SPLINE_ask_isosceles_to_pt_2d(a1, a2, a3, a4, a5, a6, a7, a8, a9,
                                      &v30, &v31, &st12, &st13);



    const __m128d v = _mm_loadu_pd(&v30.x);
    const __m128d vh = _mm_unpackhi_pd(v, v);
    const __m128d sx = _mm_add_sd(v, _mm_load_sd(&a4->x));
    const __m128d sy = _mm_add_sd(vh, _mm_load_sd(&a4->y));
    const __m128d m = _mm_mul_pd(_mm_unpacklo_pd(sx, sy), _mm_set_pd(0.5, 0.5));
    _mm_store_sd(&a10->x, m);
    _mm_store_sd(&a10->y, _mm_unpackhi_pd(m, m));

    if (a9 == 0)
    {
        const double mx = _mm_cvtsd_f64(m);
        const double my = _mm_cvtsd_f64(_mm_unpackhi_pd(m, m));
        const double ay = a7->y;
        const double ax = a7->x;
        const double dy = ay - my;
        const double dx = ax - mx;
        const double dist = sqrt(dx * dx + dy * dy);
        if (dist >= *a1)
        {
            a11->x = mx - ax;
            a11->y = my - ay;
        }
        else
        {


            const __m128d a7v = _mm_loadu_pd(&a7->x);
            const __m128d t2 = _mm_add_pd(_mm_loadu_pd(&a5->x), a7v);
            const __m128d t3 = _mm_add_pd(_mm_loadu_pd(&a3->x), a7v);
            const __m128d lo = _mm_add_sd(t2, t3);
            const __m128d hi =
                _mm_add_sd(_mm_unpackhi_pd(t2, t2), _mm_unpackhi_pd(t3, t3));
            const __m128d h =
                _mm_mul_pd(_mm_unpacklo_pd(lo, hi), _mm_set_pd(0.5, 0.5));
            a11->x = _mm_cvtsd_f64(h) - ax;
            a11->y = _mm_cvtsd_f64(_mm_unpackhi_pd(h, h)) - ay;
        }
        double len;
        VEC2_unitize(a11, 1.0e-10, &len, a11);
    }
    else
    {
        a11->x = a3->x;
        a11->y = a3->y;
    }
}
