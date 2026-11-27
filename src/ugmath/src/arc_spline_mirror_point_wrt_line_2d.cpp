












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




double __cdecl ARC_SPLINE_ask_dist_pt_to_line_2d(
    const UGS::Math::Point2* pt,
    const UGS::Math::Point2* anchor,
    const UGS::Math::Vector2* dir,
    double tol,
    UGS::Math::Point2* proj,
    double* dist,
    int* flag);

void __cdecl ARC_SPLINE_mirror_point_wrt_line_2d(
    UGS::Math::Point2* point,
    UGS::Math::Point2* anchor,
    UGS::Math::Vector2* dir,
    double tol,
    UGS::Math::Point2* out,
    int* flag)
{


    UGS::Math::Point2* res = out;
    UGS::Math::Point2 proj = {0.0, 0.0};
    res->x = 0.0;
    res->y = 0.0;

    ARC_SPLINE_ask_dist_pt_to_line_2d(point, anchor, dir, tol, &proj,
                                      (double*)&out, flag);

    __m128d pr = _mm_loadu_pd(&proj.x);
    __m128d dx = _mm_sub_sd(pr, _mm_load_sd(&point->x));
    __m128d py = _mm_unpackhi_pd(pr, pr);
    __m128d dy = _mm_sub_sd(py, _mm_load_sd(&point->y));
    _mm_storeu_pd(&res->x, _mm_add_pd(pr, _mm_unpacklo_pd(dx, dy)));
}
