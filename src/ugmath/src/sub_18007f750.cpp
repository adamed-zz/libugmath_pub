






#include <cstdint>
#include <emmintrin.h>

typedef struct
{
    char pad0[8];
    const double* x;
} View;

typedef struct
{
    char pad0[16];
    long long n;
} Src;

static __forceinline __m128d sq_at(const double* x)
{
    const __m128d v = _mm_loadu_pd(x);
    return _mm_mul_pd(v, v);
}

extern "C" __m128d sub_18007F750(const View* a, const void* unused, const Src* s)
{
    const long long n = s->n;
    const double* x = a->x;
    const long long n4 = 4 * (n / 4);
    const long long n2 = 2 * (n / 2);
    if (n2)
    {
        __m128d acc0 = sq_at(x);
        if (n2 > 2)
        {
            __m128d acc1 = sq_at(x + 2);
            for (long long k = 4; k < n4; k += 4)
            {
                acc0 = _mm_add_pd(acc0, sq_at(x + k));
                acc1 = _mm_add_pd(acc1, sq_at(x + k + 2));
            }
            acc0 = _mm_add_pd(acc0, acc1);
            if (n2 > n4)
            {
                const long long j = n4;
                acc0 = _mm_add_pd(acc0, sq_at(x + j));
            }
        }
        acc0 = _mm_add_sd(acc0, _mm_unpackhi_pd(acc0, acc0));
        if (n2 < n)
        {
            for (long long k = n2; k < n; ++k)
            {
                const __m128d v = _mm_load_sd(x + k);
                acc0 = _mm_add_sd(acc0, _mm_mul_sd(v, v));
            }
        }
        return acc0;
    }
    double sum = x[0] * x[0];
    if (n > 1)
    {
        for (long long k = 1; k < n; ++k)
            sum += x[k] * x[k];
    }
    return _mm_set_sd(sum);
}
