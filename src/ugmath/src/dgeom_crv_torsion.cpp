






#include <cmath>
#include <emmintrin.h>

double DGEOM_crv_torsion(double *a1, double *a2, double *a3, double *a4)
{
    double v11 = *(volatile double *)&a3[2];
    double v4 = a2[2];
    double v6 = a2[1];
    double v7 = a1[1];
    double v8 = a1[2];
    double v9 = a1[0];
    double v10 = v7 * v4 - v8 * v6;
    double v12 = *a2 * v8 - *a1 * v4;
    double v13 = *a3 * v4 - v11 * *a2;
    double v14 = v9 * v6 - *a2 * v7;
    double v15 = v11 * v6 - a3[1] * v4;
    double v16 = a3[1] * *a2 - *a3 * v6;
    double v17 = v12 * v12 + v10 * v10 + v14 * v14;
    double v18 = sqrt(v17);
    if (1.0e-10 > v18)
    {
        a4[2] = 0.0;
        a4[1] = 0.0;
        a4[0] = 0.0;
        return 0.0;
    }
    double v20 = v10 / v18;
    double v21 = v12 / v18;
    double v22 = v14 / v18;

    __m128d n = _mm_mul_sd(_mm_set_sd(v9), _mm_set_sd(v15));
    n = _mm_add_sd(n, _mm_mul_sd(_mm_set_sd(v7), _mm_set_sd(v13)));
    n = _mm_add_sd(n, _mm_mul_sd(_mm_set_sd(v8), _mm_set_sd(v16)));
    double v23 = _mm_cvtsd_f64(n) / (v18 * v18);
    double v24 = v9 * v9 + v7 * v7 + v8 * v8;
    double v25 = sqrt(v24);
    double v26 = v7 / v25;
    double v27 = v8 / v25;
    double v28 = v9 / v25;

    __m128d neg = _mm_set_sd(-v23);
    *a4 = _mm_cvtsd_f64(_mm_mul_sd(neg, _mm_set_sd(v27 * v21 - v26 * v22)));
    a4[1] = _mm_cvtsd_f64(_mm_mul_sd(neg, _mm_set_sd(v28 * v22 - v27 * v20)));
    a4[2] = _mm_cvtsd_f64(_mm_mul_sd(neg, _mm_set_sd(v26 * v20 - v28 * v21)));
    return v23;
}
