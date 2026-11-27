







#include <cmath>
#include <cstdint>
#include <immintrin.h>

extern "C" double ds_eq_num();
extern "C" double ds_eq_len();
extern "C" double ds_eq_len2();
extern "C" void* ds_get_acom();

static const int kType0 = 0;
static const int kType1 = 1;
static const int kType2 = 2;

static __forceinline double fsqrt(double x) {
    if (x < 0.0) return std::sqrt(x);
    return _mm_sqrt_pd(_mm_set_sd(x)).m128d_f64[0];
}

void h270(const double* a1, const double* a2, const double* a3, const double* a4, double* a5) {
    double v6 = a1[0] - a2[0];
    double v5 = a1[1] - a2[1];
    a5[0] = v6 * a3[0] + v5 * a4[0];
    a5[1] = v5 * a3[0] - v6 * a4[0];
}
