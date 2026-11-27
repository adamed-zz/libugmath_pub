









#include <emmintrin.h>
#include <stdint.h>
#include <string.h>

namespace {
inline __m128d a41_set1(uint64_t u) { return _mm_castsi128_pd(_mm_set1_epi64x((long long)u)); }


inline __m128d a41_nan_sel(__m128d dst, __m128d src, __m128d prod) {
    const __m128d qbit = a41_set1(0x0008000000000000ULL);
    __m128d md = _mm_cmpunord_pd(dst, dst);
    __m128d ms = _mm_cmpunord_pd(src, src);
    __m128d qd = _mm_or_pd(dst, qbit);
    __m128d qs = _mm_or_pd(src, qbit);
    __m128d sel = _mm_or_pd(_mm_and_pd(ms, qs), _mm_andnot_pd(ms, prod));
    return _mm_or_pd(_mm_and_pd(md, qd), _mm_andnot_pd(md, sel));
}
inline __m128d a41_mul_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_mul_pd(dst, src)); }
inline __m128d a41_add_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_add_pd(dst, src)); }
inline __m128d a41_sub_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_sub_pd(dst, src)); }
inline double a41_mul_sd(double dst, double src) { return _mm_cvtsd_f64(a41_mul_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
inline double a41_add_sd(double dst, double src) { return _mm_cvtsd_f64(a41_add_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
}

extern "C" double sub_18007EE70_cppref(void* ws, void* unused, void* cfg)
{
    (void)unused;
    const double* x = *(const double**)((char*)ws + 8);
    const double* y = *(const double**)((char*)ws + 24);
    long long n = *(const long long*)((char*)cfg + 120);

    const long long r8 = n & ~1LL;
    if (r8 == 0)
        return a41_mul_sd(y[0], x[0]);

    __m128d acc0 = a41_mul_pd(_mm_loadu_pd(x), _mm_loadu_pd(y));
    if (r8 > 2) {
        __m128d acc1 = a41_mul_pd(_mm_loadu_pd(x + 2), _mm_loadu_pd(y + 2));
        const long long v6 = n & ~3LL;
        for (long long i = 4; i < v6; i += 4) {
            acc0 = a41_add_pd(acc0, a41_mul_pd(_mm_loadu_pd(y + i), _mm_loadu_pd(x + i)));
            acc1 = a41_add_pd(acc1, a41_mul_pd(_mm_loadu_pd(y + i + 2), _mm_loadu_pd(x + i + 2)));
        }
        acc0 = a41_add_pd(acc0, acc1);
        if (r8 > v6)
            acc0 = a41_add_pd(acc0, a41_mul_pd(_mm_loadu_pd(y + v6), _mm_loadu_pd(x + v6)));
    }
    __m128d hi = _mm_unpackhi_pd(acc0, acc0);
    double sum = a41_add_sd(_mm_cvtsd_f64(acc0), _mm_cvtsd_f64(hi));
    if (r8 < n) {
        long long i = r8;
        if (n - r8 >= 4) {
            for (; i < n - 3; i += 4) {
                double p0 = a41_mul_sd(x[i], y[i]);
                double p1 = a41_mul_sd(x[i + 1], y[i + 1]);
                double p3 = a41_mul_sd(x[i + 3], y[i + 3]);
                double s0 = a41_add_sd(p0, sum);
                double p2 = a41_mul_sd(x[i + 2], y[i + 2]);
                double s1 = a41_add_sd(p1, s0);
                double s2 = a41_add_sd(p2, s1);
                sum = a41_add_sd(s2, p3);
            }
        }
        for (; i < n; ++i)
            sum = a41_add_sd(sum, a41_mul_sd(x[i], y[i]));
    }
    return sum;
}
