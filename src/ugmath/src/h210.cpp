







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

void h200(const double* a1, const double* a2, double* a3);

void h201(const double* a1, const double* a2, double* a3);

void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h210(const int* a1, const double* a2, const double* a3, const double* a4, double* a5, double* a6) {
    double v19;
    double zero = 0.0;
    int v18;
    h201(a2, a3, &v19);
    h805(&v19, &zero, &kType1, &v18);
    if (v18) {
        a5[0] = a2[0];
        a5[1] = a2[1];
        a6[0] = a3[0];
        a6[1] = a3[1];
    } else {
        double v10 = a4[0] / v19;
        if (*a1 == 1) v10 = -v10;
        double e0 = (a2[1] - a3[1]) * v10;
        double e1 = (a3[0] - a2[0]) * v10;
        a5[0] = a2[0] + e0;
        a5[1] = a2[1] + e1;
        a6[0] = a3[0] + e0;
        a6[1] = a3[1] + e1;
    }
}
