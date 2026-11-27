






#include <math.h>
#include <emmintrin.h>

void h805(const double* a1, const double* a2, const int* a3, int* a4);

void h019(const double* a1, const double* a2, const double* a3, double* a4) {
    static const double kZero = 0.0;
    static const int kMode = 1;
    int flag;
    double len2 = a3[0] * a3[0] + a3[1] * a3[1] + a3[2] * a3[2];
    double len = sqrt(len2);
    h805(&len, &kZero, &kMode, &flag);
    if (flag == 1) {
        *a4 = 0.0;
        a4[1] = 0.0;
        return;
    }
    double a20 = a2[0], a21 = a2[1], a22 = a2[2];
    double a10 = a1[0], a11 = a1[1], a12 = a1[2];
    double a30 = a3[0], a31 = a3[1], a32 = a3[2];
    double c = a21 * a11 + a20 * a10 + a22 * a12;
    double aa = a10 * a10 + a11 * a11 + a12 * a12;
    double bb = a20 * a20 + a21 * a21 + a22 * a22;
    double x1 = a30 * a10 + a31 * a11 + a32 * a12;



    const __m128d x2p1 = _mm_mul_sd(_mm_set_sd(a30), _mm_set_sd(a20));
    const __m128d x2p2 = _mm_mul_sd(_mm_set_sd(a31), _mm_set_sd(a21));
    const __m128d x2p3 = _mm_mul_sd(_mm_set_sd(a32), _mm_set_sd(a22));
    const double x2 = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(x2p1, x2p2), x2p3));
    double det = bb * aa - c * c;
    h805(&det, &kZero, &kMode, &flag);
    if (flag != 1) {
        double r1 = (x1 * bb - x2 * c) / det;
        double r2 = (x2 * aa - x1 * c) / det;
        *a4 = r1;
        a4[1] = r2;
        return;
    }
    h805(&aa, &kZero, &kMode, &flag);
    if (flag != 1) {
        *a4 = x1 / aa;
        a4[1] = 0.0;
        return;
    }
    h805(&bb, &kZero, &kMode, &flag);
    if (flag != 1) {
        *a4 = 0.0;
        a4[1] = x2 / bb;
        return;
    }
    *a4 = 0.0;
    a4[1] = 0.0;
}
