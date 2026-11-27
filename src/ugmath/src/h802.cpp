





#include <emmintrin.h>

void h802(const double* a1, const double* a2, const double* a3, const double* a4, double* a5)
{
    *a5 = 0.0;
    a5[1] = 0.0;
    a5[2] = 0.0;
    double v5 = *a2;


    if (!(0.0 >= *a2))
    {
        double v6 = *a1 / v5;
        double v7 = (v6 * 6.0 - 2.0) / v5;
        double v8 = (v6 * 6.0 - 4.0) / v5;
        double v9 = (6.0 - v6 * 12.0) / (v5 * v5);



        const __m128d m0 = _mm_mul_sd(_mm_set_sd(-v9), _mm_set_sd(a3[0]));
        const __m128d m1 = _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(a4[0]));
        const __m128d m2 = _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(a3[3]));
        const __m128d m3 = _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(a4[3]));
        *a5 = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(m0, m1), m2), m3));
        const __m128d n0 = _mm_mul_sd(_mm_set_sd(-v9), _mm_set_sd(a3[1]));
        const __m128d n1 = _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(a4[1]));
        const __m128d n2 = _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(a3[4]));
        const __m128d n3 = _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(a4[4]));
        a5[1] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(n0, n1), n2), n3));
        const __m128d p0 = _mm_mul_sd(_mm_set_sd(-v9), _mm_set_sd(a3[2]));
        const __m128d p1 = _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(a4[2]));
        const __m128d p2 = _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(a3[5]));
        const __m128d p3 = _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(a4[5]));
        a5[2] = _mm_cvtsd_f64(_mm_add_sd(_mm_add_sd(_mm_add_sd(p0, p1), p2), p3));
    }
}
