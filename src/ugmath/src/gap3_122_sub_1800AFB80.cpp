


#include <cstdint>
#include <cmath>
#include <emmintrin.h>





__declspec(dllimport) void* SM_alloc(unsigned long long n);
void SM_free(void *p);










extern "C" void sub_1800AFB80(double **a1, double *a2, double **a3, int a4, int a5,
                   int *a6, double *a7, double *a8, double a9)
{
    const __m128d absmask = _mm_castsi128_pd(_mm_set1_epi64x(0x7FFFFFFFFFFFFFFFLL));
    __m128d v12 = _mm_setzero_pd();
    __int64 n = a5;
    __int64 v9 = 0;
    if (n >= 4)
    {
        __int64 chunks = ((n - 4) >> 2) + 1;
        v9 = 4 * chunks;
        for (__int64 c = 0; c < chunks; ++c)
        {
            __m128d x0 = _mm_load_sd(&a2[4 * c + 0]);
            __m128d x1 = _mm_load_sd(&a2[4 * c + 1]);
            x0 = _mm_max_sd(x0, v12);
            __m128d x2 = _mm_load_sd(&a2[4 * c + 2]);
            v12 = _mm_load_sd(&a2[4 * c + 3]);
            x1 = _mm_max_sd(x1, x0);
            x2 = _mm_max_sd(x2, x1);
            v12 = _mm_max_sd(v12, x2);
        }
    }
    for (__int64 i = v9; i < n; ++i)
    {
        __m128d x0 = _mm_load_sd(&a2[i]);
        x0 = _mm_max_sd(x0, v12);
        v12 = x0;
    }
    v12 = _mm_mul_sd(v12, _mm_load_sd(&a9));
    double v21 = _mm_cvtsd_f64(v12);
    double *v22 = (double *)SM_alloc(8LL * a5);
    *a6 = a5;
    for (__int64 j = 0; j < n; ++j)
    {
        __m128d x3 = _mm_load_sd(&a2[j]);
        __m128d sum = _mm_setzero_pd();
        if (!(v21 >= fabs(_mm_cvtsd_f64(x3))))
        {
            __int64 m = a4;
            __int64 i = 0;
            if (m >= 4)
            {
                __int64 chunks = ((m - 4) >> 2) + 1;
                i = 4 * chunks;
                for (__int64 c = 0; c < chunks; ++c)
                {
                    __m128d p0 = _mm_mul_sd(_mm_load_sd(&a1[4 * c + 0][j]), _mm_load_sd(&a7[4 * c + 0]));
                    __m128d p1 = _mm_mul_sd(_mm_load_sd(&a1[4 * c + 1][j]), _mm_load_sd(&a7[4 * c + 1]));
                    __m128d p2 = _mm_mul_sd(_mm_load_sd(&a1[4 * c + 2][j]), _mm_load_sd(&a7[4 * c + 2]));
                    __m128d p3 = _mm_mul_sd(_mm_load_sd(&a1[4 * c + 3][j]), _mm_load_sd(&a7[4 * c + 3]));
                    sum = _mm_add_sd(sum, p0);
                    sum = _mm_add_sd(sum, p1);
                    sum = _mm_add_sd(sum, p2);
                    sum = _mm_add_sd(sum, p3);
                }
            }
            for (; i < m; ++i)
                sum = _mm_add_sd(sum, _mm_mul_sd(_mm_load_sd(&a1[i][j]), _mm_load_sd(&a7[i])));
            sum = _mm_div_sd(sum, x3);
        }
        else
        {
            --*a6;
        }
        v22[j] = _mm_cvtsd_f64(sum);
    }
    for (__int64 i = 0; i < n; ++i)
    {
        const double *vrow = a3[i];
        __m128d sum = _mm_setzero_pd();
        __int64 j = 0;
        for (; j + 4 <= n; j += 4)
        {
            __m128d p0 = _mm_mul_sd(_mm_load_sd(&v22[j + 0]), _mm_load_sd(&vrow[j + 0]));
            __m128d p1 = _mm_mul_sd(_mm_load_sd(&v22[j + 1]), _mm_load_sd(&vrow[j + 1]));
            __m128d p2 = _mm_mul_sd(_mm_load_sd(&v22[j + 2]), _mm_load_sd(&vrow[j + 2]));
            __m128d p3 = _mm_mul_sd(_mm_load_sd(&v22[j + 3]), _mm_load_sd(&vrow[j + 3]));
            __m128d t = _mm_add_sd(p0, sum);
            sum = _mm_add_sd(p1, t);
            sum = _mm_add_sd(sum, p2);
            sum = _mm_add_sd(sum, p3);
        }
        for (; j < n; ++j)
            sum = _mm_add_sd(sum, _mm_mul_sd(_mm_load_sd(&vrow[j]), _mm_load_sd(&v22[j])));
        a8[i] = _mm_cvtsd_f64(sum);
    }
    SM_free(v22);
}
