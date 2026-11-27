






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

void h601(const double* a1, const double* a2, int* a3, double* a4);

void h223(const double* a1, const double* a2, const double* a3, double* a4, double* a5) {
    *a4 = -1.0;
    double ay = a1[1];
    double ax = a1[0];
    double bx = a2[0];
    double by = a2[1];
    double cx = a3[0];
    double cy = a3[1];
    double v16[3];
    double v15[3];
    v16[0] = bx - ax;
    v16[1] = by - ay;
    v15[0] = cx - ax;
    v15[1] = cy - ay;
    v16[2] = (by + ay) * 0.5 * (by - ay) + (bx + ax) * 0.5 * (bx - ax);
    v15[2] = (cy + ay) * 0.5 * (cy - ay) + (cx + ax) * 0.5 * (cx - ax);
    int st;
    h601(v16, v15, &st, a5);
    if (st >= 2) *a4 = (a3[1] - a5[1]) * (a3[1] - a5[1]) + (a3[0] - a5[0]) * (a3[0] - a5[0]);
}
