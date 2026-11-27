







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

__declspec(noinline) void h200(const double* a1, const double* a2, double* a3) {



    __m128d v = _mm_sub_pd(_mm_loadu_pd(a1), _mm_loadu_pd(a2));
    *a3 = v.m128d_f64[0] * v.m128d_f64[0] + v.m128d_f64[1] * v.m128d_f64[1];
}

__declspec(noinline) void h806(const double* a1, const double* a2, const double* a3, int* a4) {
    *a4 = 0;
    double v = *a3;
    if (!(*a3 >= 0.0)) v = -v;
    if (v >= std::fabs(*a1 - *a2)) *a4 = 1;
}

void h204(const double* a1, const double* a2, const double* a3, int* a4) {
    double d2;
    double zero = 0.0;
    h200(a1, a2, &d2);
    double v6 = a3[0] * a3[0];
    h806(&d2, &zero, &v6, a4);
}
