




















#pragma once


namespace UGS
{
namespace Math
{
struct Vector2
{
    double x, y;
};
}
}



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);


int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out);

#include <math.h>
#include <emmintrin.h>

int VEC2_unitize(const UGS::Math::Vector2* u, double tol, double* len_out,
                 UGS::Math::Vector2* out)
{
    if (MACH__checking_level > 0 &&
        !(fabs(u->x) < 1.0e19 && fabs(u->y) < 1.0e19))
        ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\vec2.c",
                               95, "%s", "VEC2_is_finite (u)");
    double len = sqrt(u->x * u->x + u->y * u->y);
    int ok = !(tol >= len);
    if (ok)
    {
        *len_out = len;
        double inv = 1.0 / len;
        __m128d uv = _mm_loadu_pd(&u->x);
        __m128d iv = _mm_set1_pd(inv);
        _mm_storeu_pd(&out->x, _mm_mul_pd(iv, uv));
    }
    else
    {
        *len_out = 0.0;
        out->x = out->y = 0.0;
    }
    return ok;
}
