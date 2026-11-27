






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

void h264(const int* a1, const double* a2, const double* a3, const double* a4,
           const double* a5, const double* a6, double* a7) {
    double v7 = a5[0];
    double v8 = a5[1];
    double v9 = a6[0] - a2[0];
    double v10 = a6[1] - a2[1];
    if (*a1 == 1) return;
    if (*a1 != 3) {
        double p, q;
        if (*a1 == 4) {
            q = a3[0] / (v9 * v8 + v10 * v7);
            double crossq = (v10 * v8 - v9 * v7) * q;
            p = crossq / a4[0];
            double qa = std::fabs(q);
            h053(&p, &qa, a7);
        } else {
            q = (v9 * v8 + v10 * v7) / a3[0];
            double cross = v10 * v8 - v9 * v7;
            p = cross / a4[0];
            h053(&p, &q, a7);
        }
    } else {
        *a7 = v10 * v8 - v9 * v7;
    }
}
