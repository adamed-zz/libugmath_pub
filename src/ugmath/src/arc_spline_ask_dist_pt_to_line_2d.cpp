







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



double ARC_SPLINE_ask_dist_pt_to_line_2d(const Point2* pt,
                                         const Point2* origin,
                                         const Vector2* dir,
                                         double tol,
                                         Point2* closest,
                                         double* t,
                                         int* side) {
    *side = -1;

    double dy = pt->y - origin->y;
    double dx = pt->x - origin->x;
    double tt = dy * dir->y;
    tt += dx * dir->x;
    *t = tt;


    __m128d proj = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(tt), _mm_loadu_pd(&dir->x)),
                              _mm_loadu_pd(&origin->x));
    _mm_storeu_pd(&closest->x, proj);

    double dist = std::sqrt((origin->x - closest->x) * (origin->x - closest->x) +
                            (origin->y - closest->y) * (origin->y - closest->y));
    if (tol >= dist) {
        closest->x = origin->x;
        closest->y = origin->y;
        *t = 0.0;
    }

    dist = std::sqrt((closest->x - pt->x) * (closest->x - pt->x) +
                     (closest->y - pt->y) * (closest->y - pt->y));

    if (tol >= dist) {
        *side = 0;
    } else {
        double ny = -dir->y;
        *side = (ny * dx + dy * dir->x > 0.0) ? -1 : 1;
    }
    return dist;
}
