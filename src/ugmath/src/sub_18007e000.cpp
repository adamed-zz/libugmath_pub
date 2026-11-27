





















#include <cmath>
#include <emmintrin.h>
#include <stdint.h>
#include <string.h>

extern "C" char sub_18007C440(double* out, const double* A, long long p, long long q);

namespace {
inline __m128d a41_set1(uint64_t u) { return _mm_castsi128_pd(_mm_set1_epi64x((long long)u)); }


inline __m128d a41_nan_sel(__m128d dst, __m128d src, __m128d prod) {
    const __m128d qbit = a41_set1(0x0008000000000000ULL);
    __m128d md = _mm_cmpunord_sd(dst, dst);
    __m128d ms = _mm_cmpunord_sd(src, src);
    __m128d qd = _mm_or_pd(dst, qbit);
    __m128d qs = _mm_or_pd(src, qbit);
    __m128d sel = _mm_or_pd(_mm_and_pd(ms, qs), _mm_andnot_pd(ms, prod));
    return _mm_or_pd(_mm_and_pd(md, qd), _mm_andnot_pd(md, sel));
}


inline __m128d a41_mul_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_mul_sd(dst, src)); }
inline __m128d a41_add_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_add_sd(dst, src)); }
inline __m128d a41_sub_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_sub_sd(dst, src)); }
inline __m128d a41_div_pd(__m128d dst, __m128d src) { return a41_nan_sel(dst, src, _mm_div_sd(dst, src)); }
inline double a41_mul_sd(double dst, double src) { return _mm_cvtsd_f64(a41_mul_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
inline double a41_add_sd(double dst, double src) { return _mm_cvtsd_f64(a41_add_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
inline double a41_sub_sd(double dst, double src) { return _mm_cvtsd_f64(a41_sub_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
inline double a41_div_sd(double dst, double src) { return _mm_cvtsd_f64(a41_div_pd(_mm_set_sd(dst), _mm_set_sd(src))); }
}

extern "C" __declspec(noinline) char sub_18007E000(const double* A, long long p, long long q,
                                                   double* out, double* tmp) {
    const double kDblMin = 2.2250738585072014e-308;
    long long stride = *(const long long*)((const char*)A + 72);
    double g00 = A[p + p * stride];
    double g01 = A[p + q * stride];
    double g10 = A[q + p * stride];
    double g11 = A[q + q * stride];
    double b0 = g00, b1 = g01, b2 = g10, b3 = g11;
    double T = 1.0;
    double S = 0.0;
    if (!(std::fabs(a41_sub_sd(g10, g01)) < kDblMin)) {
        double t = a41_div_sd(a41_add_sd(g00, g11), a41_sub_sd(g10, g01));
        double root = std::sqrt(a41_add_sd(a41_mul_sd(t, t), 1.0));
        T = a41_div_sd(t, root);
        S = a41_div_sd(1.0, root);
        if (!(T == 1.0 && S == 0.0)) {
            b0 = a41_add_sd(a41_mul_sd(g10, S), a41_mul_sd(T, g00));
            b1 = a41_sub_sd(a41_mul_sd(T, g10), a41_mul_sd(S, g00));
            b2 = a41_add_sd(a41_mul_sd(g11, S), a41_mul_sd(T, g01));
            b3 = a41_sub_sd(a41_mul_sd(T, g11), a41_mul_sd(g01, S));
        }
    }
    double b[4] = {b0, b1, b2, b3};
    char result = sub_18007C440(tmp, b, 0, 1);
    __m128d vo0 = _mm_load_sd(&tmp[0]);
    __m128d vo1 = _mm_load_sd(&tmp[1]);
    __m128d vno1 = _mm_xor_pd(vo1, _mm_set_sd(-0.0));
    __m128d vT = _mm_set_sd(T);
    __m128d vS = _mm_set_sd(S);
    __m128d x6 = a41_mul_pd(vT, vo0);
    __m128d x7 = a41_mul_pd(vS, vno1);
    __m128d x0 = a41_mul_pd(vS, vo0);
    __m128d x3 = a41_mul_pd(vT, vno1);
    __m128d o0v = a41_sub_pd(x6, x7);
    __m128d o1v = a41_add_pd(x3, x0);
    out[0] = _mm_cvtsd_f64(o0v);
    out[1] = _mm_cvtsd_f64(o1v);
    return result;
}
