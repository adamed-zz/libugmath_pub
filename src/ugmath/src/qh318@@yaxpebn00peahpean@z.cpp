






#include <math.h>
#include <emmintrin.h>

void h318(const double* a1, const double* a2, const double* a3, int* a4, double* a5)
{
    *a4 = 1;
    double v6 = *a1 - *a2;
    double v7 = a1[1] - a2[1];
    double v8 = a1[2] - a2[2];
    double v9 = *a3 - *a2;
    double v10 = a3[1] - a2[1];
    double v11 = a3[2] - a2[2];
    __m128d sq = _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(v9));
    sq = _mm_add_sd(sq, _mm_mul_sd(_mm_set_sd(v10), _mm_set_sd(v10)));
    sq = _mm_add_sd(sq, _mm_mul_sd(_mm_set_sd(v11), _mm_set_sd(v11)));
    double v12 = _mm_cvtsd_f64(sq);
    double v13 = sqrt(v12);
    __m128d num = _mm_mul_sd(_mm_set_sd(v6), _mm_set_sd(v9));
    num = _mm_add_sd(num, _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(v10)));
    num = _mm_add_sd(num, _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v11)));
    double v14 = _mm_cvtsd_f64(_mm_div_sd(num, _mm_mul_sd(_mm_set_sd(v13), _mm_set_sd(v13))));
    *a5 = v14;
    if (v14 < 0.0 || v14 > 1.0)
        *a4 = 0;
}
