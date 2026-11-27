








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


#ifdef ARC_SEG_SELFTEST
void ERROR_internal(const char* file, int line, const char* fmt, ...);
#else
__declspec(dllimport) void ERROR_internal(const char* file, int line,
                                          const char* fmt, ...);
#endif



int VEC2_unitize(const Vector2* u, double tol, double* len_out, Vector2* out);



double ARC_SPLINE_ask_dist_pt_to_line_seg_2d(const Point2* pt,
                                             const Point2* origin,
                                             const Point2* end,
                                             double tol,
                                             int clamp,
                                             Point2* closest,
                                             double* t_out,
                                             int* pos,
                                             int* side) {
    *pos = -1;
    *side = -1;

    Vector2 d;
    d.x = end->x - origin->x;
    d.y = end->y - origin->y;

    double dx = pt->x - origin->x;
    double dy = pt->y - origin->y;

    Vector2 u = {0.0, 0.0};
    double len;
    VEC2_unitize(&d, 1.0e-10, &len, &u);
    if (len < 1.0e-10) {
        ERROR_internal(
            "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\arc_spline_apollonian_constructions.c",
            7033, "The line segment is not defined; we have coincident points.");
        __debugbreak();
    }

    double t = dy * u.y;
    t += dx * u.x;
    t /= len;


    __m128d pv = _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t), _mm_loadu_pd(&d.x)),
                            _mm_loadu_pd(&origin->x));
    double px = _mm_cvtsd_f64(pv);
    double py = _mm_cvtsd_f64(_mm_unpackhi_pd(pv, pv));

    double dist = std::sqrt((origin->x - px) * (origin->x - px) +
                            (origin->y - py) * (origin->y - py));
    if (tol >= dist) {
        px = origin->x;
        py = origin->y;
        t = 0.0;
    } else {
        double d2 = std::sqrt((end->x - px) * (end->x - px) +
                              (end->y - py) * (end->y - py));
        if (tol >= d2) {
            t = 1.0;
            px = end->x;
            py = end->y;
        }
    }

    if (clamp != 0) {
        if (t <= 0.0) {
            closest->x = origin->x;
            closest->y = origin->y;
            *t_out = 0.0;
        } else if (t >= 1.0) {
            closest->x = end->x;
            closest->y = end->y;
            *t_out = len;
        } else {
            closest->x = px;
            closest->y = py;
            *t_out = t * len;
        }
    } else {
        closest->x = px;
        closest->y = py;
        *t_out = t * len;
    }



    int posv = (t > 1.0) ? 1 : -1;
    *pos = posv;

    dist = std::sqrt((closest->x - pt->x) * (closest->x - pt->x) +
                     (closest->y - pt->y) * (closest->y - pt->y));

    if (tol >= dist) {
        *side = 0;
    } else {
        double ny = -u.y;
        *side = (ny * dx + dy * u.x > 0.0) ? -1 : 1;
    }
    return dist;
}
