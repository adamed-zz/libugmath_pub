






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

void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h053(const double* a1, const double* a2, double* a3);

void h224(const double* a1, const double* a2, const double* a3, double* a4) {
    double x = a1[0] - a3[0];
    double y = a1[1] - a3[1];
    h053(&y, &x, a4);
    double x2 = a2[0] - a3[0];
    double y2 = a2[1] - a3[1];
    h053(&y2, &x2, a4 + 1);
}
