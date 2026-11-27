















namespace UGS {
namespace Math {
struct Matrix3 {
    double m[9];
};
}
}


#include <cmath>

extern "C" __declspec(dllimport) bool RDEBUG__enabled;
extern "C" __declspec(dllimport) int RDEBUG_ask_flag(const char* name, bool default_value);
__declspec(dllimport) int lprintf(const char* format, ...);

namespace {


constexpr double kSqrEps = 1.0000000000000001e-20;

constexpr double kHi = 0.9999999999;
constexpr double kTiny = 1.0e-10;

constexpr double kRadToDeg = 57.29577951308235;


inline double sign_of(double x) { return x > 0.0 ? 1.0 : -1.0; }


void norm_pair(double* c, double* s) {
    const double c0 = *c;
    const double s0 = *s;
    const double ac = std::fabs(c0);
    const double as = std::fabs(s0);
    if (ac > kHi || as <= kTiny) {
        *s = 0.0;
        *c = sign_of(c0);
    } else if (as > kHi || ac <= kTiny) {
        *s = sign_of(s0);
        *c = 0.0;
    } else if (!(std::fabs(c0 * c0 + s0 * s0 - 1.0) <= kSqrEps)) {
        if (!(ac > as)) {
            *c = std::sqrt(1.0 - s0 * s0) * sign_of(c0);
        } else {
            *s = std::sqrt(1.0 - c0 * c0) * sign_of(s0);
        }
    }
}

}

extern "C" void sub_18009BC60(const UGS::Math::Matrix3* m, double* a2, double* a3,
                              double* a4, double* a5, double* a6, double* a7) {
    const double* a1 = m->m;
    const double sq = a1[0] * a1[0] + a1[3] * a1[3];

    if (std::fabs(sq) <= kSqrEps) {
        *a4 = 0.0;
        *a6 = 1.0;
        *a7 = 0.0;
        *a2 = a1[4];
        if (a1[6] < 0.0) {
            *a5 = 1.0;
            *a3 = a1[1];
        } else {
            *a5 = -1.0;
            *a3 = -a1[1];
        }
        norm_pair(a2, a3);
    } else {
        *a4 = std::sqrt(sq);
        *a5 = -a1[6];
        *a2 = a1[8] / *a4;
        *a3 = a1[7] / *a4;
        *a6 = a1[0] / *a4;
        *a7 = a1[3] / *a4;
        norm_pair(a4, a5);
        norm_pair(a2, a3);
        norm_pair(a6, a7);
    }
    if (RDEBUG__enabled && RDEBUG_ask_flag("UGMATH_mtx_debug", true) == 1) {
        lprintf(
            "Roll:  % 15.10f, cosine: % 15.12e, sine: % 15.12e\n"
            "Pitch: % 15.10f, cosine: % 15.12e, sine: % 15.12e\n"
            "Yaw:   % 15.10f, cosine: % 15.12e, sine: % 15.12e\n"
            "\n",
            std::atan2(*a3, *a2) * kRadToDeg, *a2, *a3,
            std::atan2(*a5, *a4) * kRadToDeg, *a4, *a5,
            std::atan2(*a7, *a6) * kRadToDeg, *a6, *a7);
    }
}
