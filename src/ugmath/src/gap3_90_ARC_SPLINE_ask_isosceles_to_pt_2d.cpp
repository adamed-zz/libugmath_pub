


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



void __declspec(noinline) ARC_SPLINE_inter_line_line_2d(
    const double* const a1, const Point2* a2, const Point2* a3, int a4,
    Vector2* a5, Vector2* a6, Point2* a7, double* a8, double* a9, int* a10);
double __declspec(noinline) ARC_SPLINE_ask_dist_pt_to_line_2d(
    const Point2* pt, const Point2* origin, const Vector2* dir, double tol,
    Point2* closest, double* t, int* side);

void ARC_SPLINE_ask_isosceles_to_pt_2d(
    double* a1, Point2* a2, Vector2* a3, Point2* a4, Vector2* a5, int a6,
    Point2* a7, double* a8, int* a9, Point2* a10, Point2* a11, int* a12,
    int* a13)
{


    int* const st = a9;

    Point2 v31 = {0.0, 0.0};
    Point2 v30 = {0.0, 0.0};

    if (!a6)
        ARC_SPLINE_inter_line_line_2d(a1, a2, a4, 1, a3, a5, a7, a8,
                                      (double*)&a9, a9);

    ARC_SPLINE_ask_dist_pt_to_line_2d(a4, a2, a3, *a1, &v30, (double*)&a9,
                                      a13);
    ARC_SPLINE_ask_dist_pt_to_line_2d(a2, a4, a5, *a1, &v31, (double*)&a9,
                                      a12);

    if (*st)
        goto out;
    if (*a12 == 0 && *a13 == 0) {
        *st = 2;
        goto out;
    }

    {
        const double t = a8[0];
        const double s = a8[1];



        int sign_t;
        if (1.0e-10 >= fabs(t - 0.0))
            sign_t = 0;
        else
            sign_t = t > 0.0 ? 1 : -1;
        _mm_storeu_pd(&a10->x,
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-(double)sign_t * fabs(s)),
                                            _mm_loadu_pd(&a3->x)),
                                 _mm_loadu_pd(&a7->x)));

        int sign_s = 0;
        if (!(1.0e-10 >= fabs(s - 0.0)))
            sign_s = s > 0.0 ? 1 : -1;
        _mm_storeu_pd(&a11->x,
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-(double)sign_s * fabs(t)),
                                            _mm_loadu_pd(&a5->x)),
                                 _mm_loadu_pd(&a7->x)));
    }
    return;

out:
    a10->x = v30.x;
    a10->y = v30.y;
    a11->x = v31.x;
    a11->y = v31.y;
}
