#include <cmath>
#include <emmintrin.h>


























namespace UGS {
namespace Math {

namespace {

inline double Minsd(double a, double b) {

    return _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

inline double Maxsd(double a, double b) {
    return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(a), _mm_set_sd(b)));
}

}

bool IntersectSegmentRectangle2D(const float* const seg, const float* const rect);

bool IntersectSegmentRectangle2D(const float* const seg, const float* const rect)
{
    const double x0 = (double)seg[0];
    const double y0 = (double)seg[1];
    const double x1 = (double)seg[2];
    const double y1 = (double)seg[3];
    double lo = x0;
    double hi = x1;
    if (x0 > x1) {
        lo = x1;
        hi = x0;
    }
    const double xmax = Minsd((double)rect[2], hi);
    const double xmin = Maxsd((double)rect[0], lo);
    if (xmin > xmax) return false;
    double ylo = y1;
    double yhi = y0;
    const double dx = x1 - x0;
    if (std::fabs(dx) > 9.999999974752427e-07) {
        const double k = (y1 - y0) / dx;
        const double b = y0 - x0 * k;
        ylo = k * xmax + b;
        yhi = k * xmin + b;
    }
    if (yhi > ylo) {
        const double t = yhi;
        yhi = ylo;
        ylo = t;
    }
    const double a = Maxsd((double)rect[1], yhi);
    const double b = Minsd((double)rect[3], ylo);
    return b >= a;
}

}
}
