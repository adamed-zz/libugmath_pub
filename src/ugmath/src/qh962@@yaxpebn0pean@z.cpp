








#include <emmintrin.h>

void b15_vunt3(const double* v, int* ok, double* out);





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

void h962(const double* a1, const double* a2, double* a3)
{
    int ok;
    h100(a1, a2, a3);
    b15_vunt3(a3, &ok, a3);
}
