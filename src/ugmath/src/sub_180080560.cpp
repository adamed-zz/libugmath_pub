








#include <cstdint>
#include <emmintrin.h>

static __forceinline __m128d sq_at(const double* p)
{
    const __m128d v = _mm_loadu_pd(p);
    return _mm_mul_pd(v, v);
}



static __forceinline double pair_max(const double* t)
{
    return (t[1] > t[0]) ? t[1] : t[0];
}



static __forceinline double tail_max(double best, double v)
{
    if (!(v <= best))
        best = v;
    return best;
}

extern "C" __m128d sub_180080560(const void* a, const void* unused, const void* s)
{
    (void)unused;

    const double* x = ((const double* const*)a)[1];
    const long long n = *(const long long*)((const char*)s + 0x18);
    const long long n4 = 4 * (n / 4);
    const long long n2 = 2 * (n / 2);
    if (!n2)
    {
        double best = x[0] * x[0];
        for (long long k = 1; k < n; ++k)
            best = tail_max(best, x[k] * x[k]);
        return _mm_set_sd(best);
    }
    __m128d acc0 = sq_at(x);
    if (n2 > 2)
    {
        __m128d acc1 = sq_at(x + 2);
        for (long long k = 4; k < n4; k += 4)
        {
            acc0 = _mm_max_pd(sq_at(x + k), acc0);
            acc1 = _mm_max_pd(sq_at(x + k + 2), acc1);
        }
        acc0 = _mm_max_pd(acc1, acc0);
        if (n2 > n4)
            acc0 = _mm_max_pd(sq_at(x + n4), acc0);
    }
    double t[2];
    _mm_storeu_pd(t, acc0);
    double best = pair_max(t);
    if (n2 < n)
    {
        for (long long k = n2; k < n; ++k)
            best = tail_max(best, x[k] * x[k]);
    }
    return _mm_set_sd(best);
}
