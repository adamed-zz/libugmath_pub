






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

void h273(const double* a1, const double* a2, const double* a3, int* a4) {
    *(volatile int*)a4 = 1;
    double v4 = std::fabs(a3[0] - a1[0]);
    double v5 = std::fabs(a3[0] - a2[0]);
    if (v4 > 3.141592653589793) v4 = 6.283185307179586 - v4;
    if (v5 > 3.141592653589793) v5 = 6.283185307179586 - v5;
    int v6 = *a4;
    if (v4 > v5) v6 = 2;
    *a4 = v6;
    if (v4 == v5) *a4 = 3;
}
