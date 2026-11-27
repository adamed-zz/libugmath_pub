







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

__declspec(noinline) void h000(double* a1) {
    double tol = ds_eq_num();
    double v3 = *a1;
    if (tol >= std::fabs(*a1 - 0.0)) {
        if (v3 >= 0.0) {
            *a1 = ds_eq_num();
            v3 = *a1;
        }
        if (!(v3 >= 0.0)) *a1 = -ds_eq_num();
    }
}

__declspec(noinline) void h704(const double* a1, const double* a2, const double* a3, double* a4, double* a5) {
    double v6 = a1[1];
    double v7 = a1[2];
    double v8 = a3[1];
    double v9 = a3[2];
    double v10 = a2[1];
    double v11 = a2[2];
    double v12 = a2[0] * a2[0] + v10 * v10 + v11 * v11;
    double v13 = a3[0] * a2[0] + v8 * v10 + v9 * v11;
    double v14 = a3[0] * a3[0] + v8 * v8 + v9 * v9;
    double v15 = a1[0] * a2[0] + v6 * v10 + v7 * v11;
    double v16 = a1[0] * a3[0] + v6 * v8 + v7 * v9;
    double v20 = v14 * v12 - v13 * v13;
    h000(&v20);
    double v18 = (v15 * v14 - v16 * v13) / v20;
    double v19 = (v16 * v12 - v15 * v13) / v20;
    *a4 = v18;
    *a5 = v19;
}


void h706(double* const a1, double* const a2, double* const a3, int* a4);

void h274(const double* a1, const double* a2, const double* a3, int* a4) {
    double v10[2] = {std::cos(a1[0]), std::sin(a1[0])};
    double v9[2] = {std::cos(a2[0]), std::sin(a2[0])};
    double v8[2] = {std::cos(a3[0]), std::sin(a3[0])};
    h706(v10, v9, v8, a4);
}
