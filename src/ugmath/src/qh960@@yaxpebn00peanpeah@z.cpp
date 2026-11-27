








#include <emmintrin.h>

void b15_vunt3(const double* v, int* ok, double* out);
void b15_vcru3(const double* u, const double* v, int* ok, double* out);

void h960(const double* a1, const double* a2, const double* a3,
          double* a4, int* a5)
{
    double v[3];

    v[0] = a2[0] - a1[0];
    v[1] = a2[1] - a1[1];
    v[2] = a2[2] - a1[2];
    b15_vunt3(v, a5, a4);

    v[0] = a3[0] - a2[0];
    v[1] = a3[1] - a2[1];
    v[2] = a3[2] - a2[2];
    b15_vunt3(v, a5, a4 + 3);

    b15_vcru3(a4, a4 + 3, a5, a4 + 6);

    if (*a5)
    {


        __m128d nx = _mm_load_sd(a4 + 6);
        __m128d ny = _mm_load_sd(a4 + 7);
        __m128d nz = _mm_load_sd(a4 + 8);
        __m128d t0 = _mm_load_sd(a4);
        __m128d t1 = _mm_load_sd(a4 + 1);
        __m128d t2 = _mm_load_sd(a4 + 2);

        __m128d r3 = _mm_sub_sd(_mm_mul_sd(ny, t2), _mm_mul_sd(nz, t1));
        __m128d r4 = _mm_sub_sd(_mm_mul_sd(t0, nz), _mm_mul_sd(nx, t2));
        __m128d r5 = _mm_sub_sd(_mm_mul_sd(nx, t1), _mm_mul_sd(t0, ny));
        _mm_store_sd(a4 + 3, r3);
        _mm_store_sd(a4 + 4, r4);
        _mm_store_sd(a4 + 5, r5);
    }
}
