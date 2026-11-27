







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

void h262(const int* a1, const double* a2, const double* a3, const double* a4, const double* a5,
           const double* a6, const double* a7, const double* a8, double* a9) {
    double v9, v10;
    if (*a1 - 3 >= 0) {
        if (*a1 == 3) {
            v10 = a4[0];
            v9 = v10 * v10 / a2[0];
        } else {
            v9 = a2[0] / a4[0];
            v10 = a3[0] * a5[0] / a4[0];
        }
    } else {
        v9 = a4[0] * a2[0];
        v10 = a3[0] * a5[0];
    }
    a9[0] = v9 * a7[0] - v10 * a8[0] + a6[0];
    a9[1] = v10 * a7[0] + v9 * a8[0] + a6[1];
}
