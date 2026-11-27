






#include <emmintrin.h>
extern int eqz(const double* a, const double* b, const int* mode);

static const double kZero430 = 0.0;
static const int kMode430 = 0;

void h430(const double* a1, const double* a2, const double* a3, double* a4)
{
    double v6 = *a3 - *a1;
    double v7 = *a2 - *a1;
    double v8 = a2[1] - a1[1];
    double v9 = a2[2] - a1[2];
    double v10 = a3[1] - a1[1];
    double v11 = a3[2] - a1[2];
    double v13 = v8 * v8 + v7 * v7 + v9 * v9;
    double v12;
    if ((unsigned int)eqz(&v13, &kZero430, &kMode430))
        v12 = 0.0;
    else
    {
        __m128d num = _mm_mul_sd(_mm_set_sd(v6), _mm_set_sd(v7));
        num = _mm_add_sd(num, _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v10)));
        num = _mm_add_sd(num, _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(v11)));
        v12 = _mm_cvtsd_f64(_mm_div_sd(num, _mm_set_sd(v13)));
    }
    *a4 = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(v12)), _mm_load_sd(a1)));
    a4[1] = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v12)), _mm_load_sd(a1 + 1)));
    a4[2] = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(v12)), _mm_load_sd(a1 + 2)));
}
