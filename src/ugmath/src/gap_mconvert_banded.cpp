







#include "b37_math.h"

void mconvert_banded(double** a1, int a2, int a3, double** a4) {
    if (a2 <= 0)
        return;

    for (int r = 0; r < a2; ++r) {
        int lo = r - a3;
        int hi = r + a3;
        double* src = a1[r];
        double* dst = a4[r];
        for (int j = 0; j < a2; ++j) {
            dst[j] = (j < lo || j > hi) ? 0.0 : src[j];
        }
    }
}
