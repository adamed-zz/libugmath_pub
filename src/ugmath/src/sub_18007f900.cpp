







#include <cstdint>
#include <cmath>
#include <emmintrin.h>

static const __m128d B30_ABS =
    _mm_castsi128_pd(_mm_set1_epi64x(0x7FFFFFFFFFFFFFFFLL));

static __forceinline __m128d abs_at(const double* p)
{
    return _mm_and_pd(_mm_loadu_pd(p), B30_ABS);
}



static __forceinline __m128d b30_max(__m128d acc, __m128d x)
{
    const __m128d m = _mm_cmpeq_pd(acc, acc);
    return _mm_or_pd(_mm_and_pd(_mm_max_pd(acc, x), m), _mm_andnot_pd(m, acc));
}


static __forceinline double hmax2(const double* p)
{
    double a = p[0];
    double b = p[1];
    const bool aok = !(a != a);
    const bool bok = !(b != b);
    const double chosen = (b > a) ? b : a;
    if (bok)
        b = chosen;
    if (aok)
        a = b;
    return a;
}

extern "C" __m128d sub_18007F900(const void* a, const void* unused, const void* s)
{
    (void)unused;
    const double* x = *(const double* const*)((const char*)a + 8);
    const long long* lp = *(const long long* const*)((const char*)s + 8);
    const long long n = 3 * lp[1];
    const long long n4 = 4 * (n / 4);
    const long long n2 = 2 * (n / 2);
    if (n2)
    {
        __m128d acc0 = abs_at(x);
        if (n2 > 2)
        {
            __m128d acc1 = abs_at(x + 2);
            for (long long k = 4; k < n4; k += 4)
            {
                acc0 = b30_max(acc0, abs_at(x + k));
                acc1 = b30_max(acc1, abs_at(x + k + 2));
            }
            acc0 = b30_max(acc0, acc1);
            if (n2 > n4)
                acc0 = b30_max(acc0, abs_at(x + n4));
        }
        double best = hmax2((const double*)&acc0);
        if (n2 < n)
        {
            for (long long k = n2; k < n; ++k)
            {
                const double av = std::fabs(x[k]);
                if (av > best)
                    best = av;
            }
        }
        return _mm_set_sd(best);
    }
    double best = std::fabs(x[0]);
    for (long long k = 1; k < n; ++k)
    {
        const double av = std::fabs(x[k]);
        if (av > best)
            best = av;
    }
    return _mm_set_sd(best);
}
