





#include <math.h>
void e4322(int* a1, int* a2, double* a3, double* a4, int* a5);

void em0925_a(int a1, int a2, double* a3, double a4, int* a5, int* a6) {
    static const double kTol = 1.0e-10;
    int v19;
    int v20;
    int v21;
    double v22;
    v22 = a4;
    v19 = a1;
    v21 = a1 + a2;
    e4322(&v19, &v21, a3, &v22, &v20);

    int v8 = 0;
    int b;
    --v20;
    int v13 = v20;
    int v10 = v20;
    int v11 = v19;
    b = fabs(v22 - a3[v20 - 1]) < kTol;
    if (b) {
        do {
            v10 = v13;
            if (v13 <= v19) break;
            --v13;
            v20 = v13;
            v10 = v13;
            b = fabs(v22 - a3[v20 - 1]) < kTol;
        } while (b);
    }
    long long v15 = v10 - 1;
    long long v16 = v10 + v19;
    if (v15 < v16) {
        for (long long i = v15; i < v16; ++i) {
            if (fabs(a3[i] - v22) < kTol) ++v8;
        }
    }
    *a5 = v20;
    *a6 = a2 + v11 - v8 - v20;
}
