







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

__declspec(noinline) void h301(const double* a1, const double* a2, double* a3) {
    double dz = a1[2] - a2[2];
    double dy = a1[1] - a2[1];
    double dx = a1[0] - a2[0];
    double s = dy * dy + dx * dx + dz * dz;
    *a3 = fsqrt(s);
}

void h205(const double* a1, double* a2, int* a3) {
    double v6, v7, v8;
    *a3 = 0;
    h301(a1, a2, &v8);
    h301(a2, a2 + 3, &v6);
    h301(a1, a2 + 3, &v7);
    if (v7 >= v8 && v7 >= v6) {
        a2[0] = a1[0];
        a2[1] = a1[1];
        a2[2] = a1[2];
        *a3 = 1;
        return;
    }
    if (v8 >= v6 && v8 >= v7) {
        a2[3] = a1[0];
        a2[4] = a1[1];
        a2[5] = a1[2];
        *a3 = 1;
    }
}
