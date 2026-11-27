






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

int eqz(const double* a1, const double* a2, const int* a3);

void h230(const double* a1, const double* a2, int* a3, double* a4, double* a5, double* a6) {
    *a3 = 1;
    double zero = 0.0;
    double v11 = -(a2[0] - a1[0]);
    double v10 = a2[1] - a1[1];
    double v12 = a2[0] * a1[1] - a2[1] * a1[0];
    double v16 = v11 * v11 + v10 * v10;
    if (eqz(&v16, &zero, &kType0)) {
        *a3 = 2;
    } else {
        double len = fsqrt(v12 * v12 + v16);
        a4[0] = v10 / len;
        a5[0] = v11 / len;
        a6[0] = v12 / len;
    }
}
