











#include "b37_math.h"

#include <cmath>

void mdecompose_banded(double** a1, int a2, int a3) {
    const int n = a2;
    const int m = a3;
    if (m < 1)
        return;
    if (n <= 1)
        return;

    for (int r = 1; r < n; ++r) {
        int k0 = r - m;
        if (k0 < 0)
            k0 = 0;
        for (int k = k0; k < r; ++k) {
            double pivot = a1[k][k];
            if (std::fabs(pivot) < 1.0e-15) {
                merrorpush((char* const) "", 7235, 4);
                return;
            }
            double f = a1[r][k] / pivot;
            a1[r][k] = f;
            const int jmax = m + k;
            for (int j = k + 1; j < n && j <= jmax; ++j)
                a1[r][j] -= f * a1[k][j];
        }
    }
}
