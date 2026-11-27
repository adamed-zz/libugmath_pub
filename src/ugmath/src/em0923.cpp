











#include <cstring>
#include <emmintrin.h>

#define B6_LD(p, i) _mm_loadu_pd((p) + (i))
#define B6_ST(p, i, v) _mm_storeu_pd((p) + (i), (v))

void em0923(int* a1, double* a2, double (*a3)[4], double* a4,
            double (*a5)[4], double (*a6)[4]) {
    double L[2600];
    const int n = *a1;
    const double c = *a4;

    for (int i = 0; i < 24; i++) {
        L[i] = 0.0;
        L[24 + i] = 0.0;
    }



    int v11 = 0;
    if (n >= 4) {
        int v29 = ((n - 4) >> 2) + 1;
        v11 = 4 * v29;
        for (int k = 0; k < v29; k++) {
            int q = 4 * k;
            for (int j = 0; j < 4; j++) {
                L[q + j] = a2[n + 1 + q + j] - c;
                L[24 + q + j] = c - a2[1 + q + j];
            }
        }
    }
    for (int k = v11; k < n; k++) {
        L[k] = a2[n + 1 + k] - c;
        L[24 + k] = c - a2[1 + k];
    }


    if (n >= 0) {
        for (int i = 0; i <= n; i++) {
            for (int t = 0; t < 4; t++)
                L[48 + 4 * i + t] = a3[i][t];
        }
    }
    if (n < 0)
        return;



    if (n >= 1) {
        for (int cstep = 1; cstep <= n; cstep++) {
            double* rowp = L + 50 + 104 * (cstep - 1);
            __m128d v47 = B6_LD(rowp, 0);
            int inner = n - cstep + 1;
            for (int i = 0; i < inner; i++) {
                double b0 = L[i];
                double b1 = L[24 + i + (cstep - 1)];
                __m128d A = _mm_set1_pd(b0);
                __m128d Bv = _mm_set1_pd(b1);
                __m128d S = _mm_set1_pd(b0 + b1);
                __m128d prev = B6_LD(rowp, 4 * i - 2);
                __m128d next = B6_LD(rowp, 4 * i + 2);
                __m128d next2 = B6_LD(rowp, 4 * i + 4);
                B6_ST(rowp, 4 * i + 102,
                      _mm_div_pd(_mm_add_pd(_mm_mul_pd(prev, A),
                                            _mm_mul_pd(next, Bv)), S));
                __m128d v56 = _mm_add_pd(_mm_mul_pd(next2, Bv),
                                         _mm_mul_pd(v47, A));
                v47 = next2;
                B6_ST(rowp, 4 * i + 104, _mm_div_pd(v56, S));
            }
        }
    }


    {
        double* dst = (double*)a5;
        for (int j = 0; j <= n; j++) {
            for (int t = 0; t < 4; t++)
                dst[4 * j + t] = L[48 + 104 * j + t];
        }
    }

    {
        double* dst = (double*)a6;
        int idx = 48 + 104 * n;
        for (int t = 0; t <= n; t++) {
            for (int k = 0; k < 4; k++)
                dst[4 * t + k] = L[idx + k];
            idx -= 100;
        }
    }
}
