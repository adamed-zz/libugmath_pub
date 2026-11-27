





#include <cmath>
#include <xmmintrin.h>
#include <emmintrin.h>

__m128d sub_1800B2800(double* a1, double* a2)
{
    __m128d pd = _mm_load_sd(a2);
    __m128d px = _mm_load_sd(a1);
    double v = _mm_cvtsd_f64(_mm_div_sd(px, pd));
    double q;
    if (v < 0.0)
        q = -floor(-v);
    else
        q = floor(v);
    double res = _mm_cvtsd_f64(px) - _mm_cvtsd_f64(pd) * q;
    return _mm_set_sd(res);
}
