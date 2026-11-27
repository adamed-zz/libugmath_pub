






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

void h222(const int* a1, const double* a2, const double* a3, const double* a4, const double* a5, double* a6) {
    double v8 = a4[0] - a3[0];
    double v9 = a5[0] - a3[0];
    double v10 = a5[1] - a3[1];
    double v11 = a4[1] - a3[1];
    double v16[2] = {v8, v11};
    double v15[2] = {v9, v10};
    if (*a1 != 1) {
        v16[0] = v9;
        v16[1] = v10;
        v15[0] = v8;
        v15[1] = v11;
    }
    double v17, v18;
    h053(&v16[1], &v16[0], &v17);
    h053(&v15[1], &v15[0], &v18);
    int flag;
    h805(&v17, &v18, &kType0, &flag);
    double v13;
    if (flag) {
        v13 = 6.283185307179586;
    } else {
        double v12 = v18;
        if (v17 >= v18) v12 = v18 + 6.283185307179586;
        v13 = v12 - v17;
    }
    *a6 = v13;
    *a6 = v13 * a2[0];
}
