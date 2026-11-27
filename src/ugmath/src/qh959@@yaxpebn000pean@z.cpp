








#include <emmintrin.h>

__declspec(noinline) static void movf_copy(const int* count, const double* src, double* dst)
{

    for (int i = 0; i < *count; ++i)
        dst[i] = src[i];
}


__declspec(noinline) static void h110(const double* a1, double* a2)
{
    a2[0] = a1[0];
    a2[4] = a1[4];
    a2[8] = a1[8];
    a2[3] = a1[1];
    *(long long*)(a2 + 1) = *(const long long*)(a1 + 3);
    a2[6] = a1[2];
    *(long long*)(a2 + 2) = *(const long long*)(a1 + 6);
    a2[7] = a1[5];
    *(long long*)(a2 + 5) = *(const long long*)(a1 + 7);
}





__declspec(noinline) static void h100(const double* a1, const double* a2, double* a3)
{
    __m128d x = _mm_load_sd(a1);
    __m128d y = _mm_load_sd(a1 + 1);
    __m128d z = _mm_load_sd(a1 + 2);

    __m128d r0 = _mm_mul_sd(y, _mm_load_sd(a2 + 1));
    r0 = _mm_add_sd(r0, _mm_mul_sd(x, _mm_load_sd(a2)));
    r0 = _mm_add_sd(r0, _mm_mul_sd(z, _mm_load_sd(a2 + 2)));
    _mm_store_sd(a3, r0);

    __m128d r1 = _mm_mul_sd(x, _mm_load_sd(a2 + 3));
    r1 = _mm_add_sd(r1, _mm_mul_sd(y, _mm_load_sd(a2 + 4)));
    r1 = _mm_add_sd(r1, _mm_mul_sd(z, _mm_load_sd(a2 + 5)));
    _mm_store_sd(a3 + 1, r1);

    __m128d r2 = _mm_mul_sd(x, _mm_load_sd(a2 + 6));
    r2 = _mm_add_sd(r2, _mm_mul_sd(y, _mm_load_sd(a2 + 7)));
    r2 = _mm_add_sd(r2, _mm_mul_sd(z, _mm_load_sd(a2 + 8)));
    _mm_store_sd(a3 + 2, r2);
}



__declspec(noinline) static void h956(const double* a1, const double* a2, double* a3)
{
    h100(a1, a2, a3);
    __m128d t0 = _mm_add_sd(_mm_load_sd(a2 + 9), _mm_load_sd(a3));
    __m128d t1 = _mm_add_sd(_mm_load_sd(a2 + 10), _mm_load_sd(a3 + 1));
    __m128d t2 = _mm_add_sd(_mm_load_sd(a2 + 11), _mm_load_sd(a3 + 2));
    _mm_store_sd(a3, t0);
    _mm_store_sd(a3 + 1, t1);
    _mm_store_sd(a3 + 2, t2);
}



__declspec(noinline) static void h957(const double* a1, const double* a2, const double* a3,
                     const double* a4, double* a5)
{
    double v8[3];
    double v9[3];
    double v10[9];
    h110(a3, v10);
    h100(a1, v10, v8);
    h956(v8, a2, v9);
    h100(v9, a4, a5);
}

void h959(const double* a1, const double* a2, const double* a3,
          const double* a4, double* a5)
{
    double v8[3];
    double v9[3];
    double v10[9];
    double v11[3];
    const int c2 = 2;
    const int c9 = 9;
    const int c3 = 3;
    static const double zeros[3] = {0.0, 0.0, 0.0};

    movf_copy(&c2, a1, v8);
    v8[2] = 0.0;
    movf_copy(&c9, a2, v10);
    movf_copy(&c3, zeros, v11);
    h957(v8, v10, a3, a4, v9);
    movf_copy(&c2, v9, a5);
}
