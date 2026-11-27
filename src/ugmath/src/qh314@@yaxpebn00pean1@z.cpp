






#include <emmintrin.h>
extern void h805(const double* a, const double* b, const int* mode, int* out);

static const double kZero314 = 0.0;
static const int kMode314 = 0;

void h314(const double* a1, const double* a2, const double* a3, double* a4, double* a5)
{
    double v6 = a3[1] - a1[1];
    double v8 = a2[1] - a1[1];
    double v9 = *a3 - *a1;
    double v10 = *a2 - *a1;
    double v14 = _mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v8)),
                                       _mm_mul_sd(_mm_set_sd(v10), _mm_set_sd(v10))));
    int v13;
    h805(&v14, &kZero314, &kMode314, &v13);
    if (v13 == 1)
    {
        *a5 = 0.0;
        *a4 = *a1;
        a4[1] = a1[1];
    }
    else
    {
        __m128d num = _mm_add_sd(_mm_mul_sd(_mm_set_sd(v6), _mm_set_sd(v8)),
                                _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(v10)));
        double v12 = _mm_cvtsd_f64(_mm_div_sd(num, _mm_set_sd(v14)));
        *a5 = v12;
        *a4 = v12 * v10 + *a1;
        a4[1] = v8 * *a5 + a1[1];
    }
}
