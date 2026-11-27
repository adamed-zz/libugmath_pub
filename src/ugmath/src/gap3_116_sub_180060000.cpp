
















#include <math.h>

extern "C" void sub_180060000(const double* x, int n, int m, double* p, const double* y,
                              double* J, int unused_a7, int* status, double eps, double* work) {
    (void)unused_a7;
    const double t = fmax(eps, 1.2e-16);
    const double v15 = sqrt(t);

    if (m <= 0) return;
    __int64 row = 0;
    for (int j = 0; j < m; ++j) {
        const double v20 = p[j];
        double v21 = fabs(v20) * v15;
        if (!(v21 != 0.0)) v21 = v15;
        p[j] = v21 + v20;

        for (int i = 0; i < n; ++i) {
            const double x0 = x[2 * i];
            const double x1 = x[2 * i + 1];
            work[i] = (p[0] + p[0]) * x0 * x1 + x0 * x0 + x1 * p[1] * x1 +
                      (p[2] + p[2]) * x0 + (p[3] + p[3]) * x1 + p[4];
        }

        if (*status < 0) break;
        p[j] = v20;

        for (int i = 0; i < n; ++i) {
            J[row + i] = (work[i] - y[i]) / v21;
        }
        row += n;
    }
}
