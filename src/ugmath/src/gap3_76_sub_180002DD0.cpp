




#include <emmintrin.h>

extern "C" __int64 __fastcall sub_180002DD0(double *a1, double a2, double *a3, double a4,
                                            double *a5, double *a6)
{
    __m128d v7 = _mm_load_sd(a1);
    __m128d v12 = _mm_load_sd(a1 + 1);
    __m128d v10 = _mm_load_sd(a3);
    __m128d v8 = _mm_load_sd(a3 + 1);
    __m128d two = _mm_set1_pd(2.0);
    __m128d v13 = _mm_mul_pd(two, _mm_unpacklo_pd(v7, v12));
    *((char *)a5 + 32) = 0;
    *((char *)a6 + 32) = 0;
    __m128d v14 = _mm_mul_pd(two, _mm_unpacklo_pd(v10, v8));
    double v15 = v13.m128d_f64[0] * a4;
    double v16 = v14.m128d_f64[0] * a2;
    v14.m128d_f64[0] = _mm_unpackhi_pd(v14, v14).m128d_f64[0] * a2;
    double v17 = v16 + v15;
    v13.m128d_f64[0] = _mm_unpackhi_pd(v13, v13).m128d_f64[0] * a4;
    a5[0] = v17;
    a6[0] = v15 - v16;
    a5[1] = v14.m128d_f64[0] + v13.m128d_f64[0];
    a6[1] = v13.m128d_f64[0] - v14.m128d_f64[0];
    a5[2] = a2 * -1.0 + a4 * -1.0;
    a6[2] = a4 * -1.0 - a2 * -1.0;
    v12.m128d_f64[0] = -(v12.m128d_f64[0] * v12.m128d_f64[0] + v7.m128d_f64[0] * v7.m128d_f64[0]
                         - a2 * a2) * a4;
    v8.m128d_f64[0] = -(v8.m128d_f64[0] * v8.m128d_f64[0] + v10.m128d_f64[0] * v10.m128d_f64[0]
                        - a4 * a4) * a2;
    a5[3] = v8.m128d_f64[0] + v12.m128d_f64[0];
    a6[3] = v12.m128d_f64[0] - v8.m128d_f64[0];
    return (__int64)a5;
}
