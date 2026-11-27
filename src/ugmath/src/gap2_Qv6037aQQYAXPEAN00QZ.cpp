
#include <cstring>
#include <xmmintrin.h>
#include <emmintrin.h>

void h923(double* a, double* b, double* out);
void h110(const double* src, double* dst);
void h120(const double* a, const double* b, double* out);

void v6037a(double* a1, double* a2, double* a3)
{
    alignas(16) double m[9];
    alignas(16) double t[9];
    std::memcpy(a3, a1, 9 * sizeof(double));
    const double k = 0.01745329251994328;
    double v6 = a2[1] * k;
    double v0 = *a2 * k;
    *reinterpret_cast<volatile double*>(a2) = v0;
    double v7 = a2[2] * k;
    a2[1] = v6;
    a2[2] = v7;
    double* v3 = a2 + 1;
    double* v5 = a2 + 2;
    h923(a1, a2, t);
    h110(t, m);
    h120(m, a3, t);
    h923(t + 3, v3, a3);
    h110(a3, m);
    h120(m, t, a3);
    h923(a3 + 6, v5, m);
    h110(m, t);
    h120(t, a3, m);
    _mm_storeu_pd(a3 + 0, _mm_castps_pd(*reinterpret_cast<const __m128*>(m + 0)));
    _mm_storeu_pd(a3 + 2, _mm_castps_pd(*reinterpret_cast<const __m128*>(m + 2)));
    _mm_storeu_pd(a3 + 4, _mm_castps_pd(*reinterpret_cast<const __m128*>(m + 4)));
    _mm_storeu_pd(a3 + 6, _mm_castps_pd(*reinterpret_cast<const __m128*>(m + 6)));
    a3[8] = m[8];
}
