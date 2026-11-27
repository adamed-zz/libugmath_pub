






#include <cstdint>
#include <emmintrin.h>

typedef struct
{
    char pad0[8];
    const double* x;
    char pad16[8];
    const double* y;
} View;

typedef struct
{
    char pad0[0xA0];
    long long n;
} Src;

static __forceinline __m128d mulpd_at(const double* x, const double* y)
{
    return _mm_mul_pd(_mm_loadu_pd(x), _mm_loadu_pd(y));
}

extern "C" __m128d sub_18007F0C0(const View* a, const void* unused, const Src* s)
{
    const long long n = s->n;
    const double* x = a->x;
    const double* y = a->y;
    const long long n4 = 4 * (n / 4);
    const long long n2 = 2 * (n / 2);
    if (n2)
    {
        __m128d acc0 = mulpd_at(x, y);
        if (n2 > 2)
        {
            __m128d acc1 = mulpd_at(x + 2, y + 2);
            if (n4 > 4)
            {
                long long k = 4;
                do
                {
                    acc0 = _mm_add_pd(acc0, mulpd_at(x + k, y + k));
                    acc1 = _mm_add_pd(acc1, mulpd_at(x + k + 2, y + k + 2));
                    k += 4;
                } while (k < n4);
            }
            acc0 = _mm_add_pd(acc0, acc1);
            if (n2 > n4)
            {
                const long long j = n4;
                acc0 = _mm_add_pd(acc0, mulpd_at(x + j, y + j));
            }
        }
        acc0 = _mm_add_sd(acc0, _mm_unpackhi_pd(acc0, acc0));
        if (n2 < n)
        {
            long long k = n2;
            for (; k < n; ++k)
                acc0 = _mm_add_sd(acc0, _mm_mul_sd(_mm_load_sd(x + k), _mm_load_sd(y + k)));
        }
        return acc0;
    }
    double sum = x[0] * y[0];
    if (n > 1)
    {
        for (long long k = 1; k < n; ++k)
            sum += x[k] * y[k];
    }
    return _mm_set_sd(sum);
}
