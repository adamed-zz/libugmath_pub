#include <cmath>
#include <xmmintrin.h>
#include <emmintrin.h>

namespace UGS {
namespace Math {
struct Vector2 {
    double x, y;
};
}
}

namespace {
const int g_checking_level = 0;
}

void ERROR_assertion_failed(const char* file, int line, const char* fmt, ...);

int VEC2_ask_perpendicular(const UGS::Math::Vector2* a1, UGS::Math::Vector2* a2)
{
    if (g_checking_level > 0 && (fabs(a1->x) >= 1.0e19 || fabs(a1->y) >= 1.0e19))
        ERROR_assertion_failed("o:\nx2412\ip1700\src\ugmath\no\ind\vec2.c", 218, "%s",
                               "VEC2_is_finite (u)");
    const double v4 = a1->y;
    const double v5 = a1->x;
    __m128d v6 = _mm_set_sd(v5 * v5 + v4 * v4);
    double v7;
    if (v6.m128d_f64[0] < 0.0)
        v7 = sqrt(v6.m128d_f64[0]);
    else
        v7 = _mm_sqrt_pd(v6).m128d_f64[0];
    const int result = !(v7 <= 1.0e-10);
    double v9;
    if (result) {
        if (fabs(v4) > fabs(v5)) {
            a2->x = -v4;
            v9 = a1->x;
        } else {
            a2->x = v4;
            v9 = -a1->x;
        }
    } else {
        *reinterpret_cast<double*>(a2) = 0;
        v9 = 0.0;
    }
    a2->y = v9;
    return result;
}
