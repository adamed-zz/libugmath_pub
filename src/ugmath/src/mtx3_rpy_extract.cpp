




















#include "ugmath/matrix3.h"

#include <cmath>

#include "mtx3_rpy_extract.h"

namespace {

constexpr double kHi = 0.9999999999;
constexpr double kTiny = 1.0e-10;




constexpr double kEps = 1.0000000000000001e-20;


inline double sign_from_compare(double x) {
    return (x > 0.0) ? 1.0 : -1.0;
}


void norm_pair(double* c, double* s) {
    const double c0 = *c;
    const double s0 = *s;
    const double ac = std::fabs(c0);
    const double as = std::fabs(s0);
    if (ac > kHi || as <= kTiny) {

        *s = 0.0;
        *c = sign_from_compare(c0);
    } else if (as > kHi || ac <= kTiny) {

        *s = sign_from_compare(s0);
        *c = 0.0;
    } else if (!(std::fabs(c0 * c0 + s0 * s0 - 1.0) <= kEps)) {

        if (!(ac > as)) {
            *c = std::sqrt(1.0 - s0 * s0) * sign_from_compare(c0);
        } else {
            *s = std::sqrt(1.0 - c0 * c0) * sign_from_compare(s0);
        }
    }

}

}

void MTX3_rpy_extract(const UGS::Math::Matrix3* m, double* a2, double* a3, double* a4,
                      double* a5, double* a6, double* a7) {
    const double* a1 = m->m;
    const double sq = a1[0] * a1[0] + a1[3] * a1[3];

    if (!(std::fabs(sq) <= kEps)) {
        const double c = std::sqrt(sq);
        *a4 = c;
        *a5 = -a1[6];
        *a2 = a1[8] / *a4;
        *a3 = a1[7] / *a4;
        *a6 = a1[0] / *a4;
        *a7 = a1[3] / *a4;
        norm_pair(a4, a5);
        norm_pair(a2, a3);
        norm_pair(a6, a7);
    } else {

        *a4 = 0.0;
        *a6 = 1.0;
        *a7 = 0.0;
        *a2 = a1[4];
        if (!(a1[6] < 0.0)) {
            *a5 = -1.0;
            *a3 = -a1[1];
        } else {
            *a5 = 1.0;
            *a3 = a1[1];
        }
        norm_pair(a2, a3);
    }
}
