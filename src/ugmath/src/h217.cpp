







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

__declspec(noinline) int vec2_unitize(const double* u, double tol, double* lenOut, double* out) {
    double len = fsqrt(u[0] * u[0] + u[1] * u[1]);


    int result = !(tol >= len);
    if (tol >= len) {
        *lenOut = 0.0;
        out[0] = 0.0;
        out[1] = 0.0;
    } else {
        *lenOut = len;
        double inv = 1.0 / len;
        out[0] = inv * u[0];
        out[1] = inv * u[1];
    }
    return result;
}

__declspec(noinline) void vunt2(const double* a1, int* a2, double* a3) {
    double len;
    *a2 = vec2_unitize(a1, ds_eq_len(), &len, a3);
}

void h217(const double* a1, const double* a2, double* a3) {
    double v7 = a2[1] * a1[2] - a2[2] * a1[1];
    double v8 = a1[0] * a2[2] - a2[0] * a1[2];
    double v9 = a2[0] * a1[1] - a1[0] * a2[1];
    double v11[2];
    v11[0] = a1[1] * v9 - a1[2] * v8;
    v11[1] = a1[2] * v7 - a1[0] * v9;
    int st;
    vunt2(v11, &st, a3);
    a3[0] = -a3[0];
    a3[1] = -a3[1];
}
