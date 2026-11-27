








#include "b37_math.h"

#include <cmath>

void msolve_banded(double** a1, int a2, int a3, double* a4) {
    const int n = a2;
    const int m = a3;

    if (n > 1) {
        for (int i = 1; i < n; ++i) {
            int lo = i - m;
            if (lo < 0)
                lo = 0;
            if (lo < i) {
                double v = a4[i];
                for (int k = lo; k < i; ++k) {
                    v -= a1[i][k] * a4[k];
                    a4[i] = v;
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int jmax = i + m;
        for (int j = i + 1; j < n && j <= jmax; ++j)
            a4[i] -= a1[i][j] * a4[j];
        if (1.0e-15 > std::fabs(a1[i][i])) {
            merrorpush((char* const) "", 7235, 4);
            return;
        }
        a4[i] /= a1[i][i];
    }
}
