







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

void h272b(const double* a1, const double* a2, const double* a3, const int* a4, int* a5) {
    *(volatile int*)a5 = 0;
    double v5 = (*a4 == 1) ? 0.000001 : 0.0;
    int v6 = *a5;
    if (v5 > std::fabs(a1[0] * a3[1] - a1[1] * a3[0] + a2[0])) v6 = 1;
    *a5 = v6;
}
