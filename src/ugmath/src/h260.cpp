






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

void h260(const int* a1, const double* a2, const double* a3, const double* a4, const double* a5, const double* a6, double* a7) {
    double v7 = a5[0] * a5[0];
    double v8 = a6[0] * a6[0];
    double v13, v12, v14;
    if (*a1 - 3 >= 0) {
        if (*a1 == 3) {
            a7[0] = v8;
            double v15 = a5[0] * -2.0 * a6[0];
            a7[2] = v7;
            a7[1] = v15;
            a7[3] = -a3[0] * a5[0] - (a2[0] + a2[0]) * v8 - v15 * a2[1];
            a7[4] = -a3[0] * a6[0] - v15 * a2[0] - (a2[1] + a2[1]) * v7;
            a7[5] = (a2[0] * a5[0] + a2[1] * a6[0]) * a3[0] + a2[0] * v8 * a2[0]
                    + a2[0] * v15 * a2[1] + a2[1] * v7 * a2[1];
            return;
        }
        double v16 = a3[0] * a3[0];
        double v17 = a4[0] * a4[0];
        v13 = v7 / v16 - v8 / v17;
        v12 = v8 / v16 - v7 / v17;
        v14 = 1.0 / v17 + 1.0 / v16;
    } else {
        double v9 = a3[0] * a3[0];
        double v10 = a4[0] * a4[0];
        double v11 = v7 / v9;
        v12 = v7 / v10 + v8 / v9;
        v13 = v8 / v10 + v11;
        v14 = 1.0 / v9 - 1.0 / v10;
    }
    a7[0] = v13;
    a7[1] = v14 * ((a5[0] + a5[0]) * a6[0]);
    a7[2] = v12;
    double v18 = a7[1];
    a7[3] = a2[0] * -2.0 * v13 - v18 * a2[1];
    a7[4] = -a2[0] * v18 - (a2[1] + a2[1]) * v12;
    a7[5] = a2[0] * v13 * a2[0] + a2[0] * v18 * a2[1] + v12 * a2[1] * a2[1] - 1.0;
}
