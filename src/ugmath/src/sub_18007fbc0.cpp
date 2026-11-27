







#include <cstdint>
#include <emmintrin.h>

static __forceinline __m128d load2(const double* p)
{
    return _mm_loadu_pd(p);
}

static __forceinline __m128d b30_max(__m128d acc, __m128d x)
{
    const __m128d m = _mm_cmpeq_pd(acc, acc);
    return _mm_or_pd(_mm_and_pd(_mm_max_pd(acc, x), m), _mm_andnot_pd(m, acc));
}

extern "C" __m128d sub_18007FBC0(const void* a, const void* unused, const void* s)
{
    (void)unused;
    const double* x = *(const double* const*)a;
    const long long n = *(const long long*)((const char*)s + 8);
    const long long n4 = 4 * (n / 4);
    const long long n2 = 2 * (n / 2);
    if (!n2)
    {
        double best = x[0];
        for (long long k = 1; k < n; ++k)
            if (x[k] > best)
                best = x[k];
        return _mm_set_sd(best);
    }
    __m128d acc0 = load2(x);
    if (n2 > 2)
    {
        __m128d acc1 = load2(x + 2);
        for (long long k = 4; k < n4; k += 4)
        {
            acc0 = b30_max(acc0, load2(x + k));
            acc1 = b30_max(acc1, load2(x + k + 2));
        }
        acc0 = b30_max(acc0, acc1);
        if (n2 > n4)
            acc0 = b30_max(acc0, load2(x + n4));
    }
    double t[2];
    _mm_storeu_pd(t, acc0);
    double best = (t[1] > t[0]) ? t[1] : t[0];
    for (long long k = n2; k < n; ++k)
        if (x[k] > best)
            best = x[k];
    return _mm_set_sd(best);
}
