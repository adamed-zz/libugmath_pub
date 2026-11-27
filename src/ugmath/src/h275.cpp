






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

__declspec(noinline) void h100(const double* a1, const double* a2, double* a3) {
    double x = a1[0];
    double y = a1[1];
    double z = a1[2];
    a3[0] = y * a2[1] + x * a2[0] + z * a2[2];
    a3[1] = x * a2[3] + y * a2[4] + z * a2[5];
    a3[2] = x * a2[6] + y * a2[7] + z * a2[8];
}

__declspec(noinline) void h110(const double* a1, double* a2) {
    a2[0] = a1[0];
    a2[4] = a1[4];
    a2[8] = a1[8];
    double t3 = a1[3];
    double t1 = a1[1];
    a2[3] = t1;
    a2[1] = t3;
    double t6 = a1[6];
    double t2 = a1[2];
    a2[6] = t2;
    a2[2] = t6;
    double t7 = a1[7];
    double t5 = a1[5];
    a2[7] = t5;
    a2[5] = t7;
}

void h275(const double* a1, const double* a2, const double* a3, const double* a4, double* a5) {
    double d[3] = {a1[0] - a3[0], a1[1] - a3[1], a1[2] - a3[2]};
    double v17[3];
    h100(d, a2, v17);
    double c = std::cos(a4[0]);
    double s = std::sin(a4[0]);
    double v14[3];
    v14[1] = s * v17[0] + c * v17[1];
    v14[2] = v17[2];
    v14[0] = c * v17[0] - s * v17[1];
    double v20[9];
    h110(a2, v20);
    h100(v14, v20, a5);
    double v12 = a5[1] + a3[1];
    double v13 = a3[2] + a5[2];
    a5[0] = a3[0] + a5[0];
    a5[1] = v12;
    a5[2] = v13;
}
