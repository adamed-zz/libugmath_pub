





















#include "ugmath/b37_math.h"

extern "C" {

int b37_a1ab0_state = 0;
}

long long sub_1800A1AB0(long long a1, b37_deriv_a a2, int a3, double a4, double a5, int a6,
                        double* a7) {
    const int n = a3;

    if (a6 == 1) {
        b37_a1ab0_state = 1;

        double xa = a4;
        double xb = a5;
        double out1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        double out2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int err = a6;

        long long r1 = a2(a1, &xa, out1, &err);
        (void)r1;
        long long r2 = a2(a1, &xb, out2, &err);

        double f = (a5 - a4) * 0.5;
        for (int i = 0; i < n; ++i)
            a7[i] = (out2[i] + out1[i]) * f;

        return (n <= 0) ? r2 : 0;
    }

    int g = b37_a1ab0_state;
    double dx = (a5 - a4) / (double)g;
    double x = a4 + dx * 0.5;

    double accum[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (n > 0) {
        for (int i = 0; i < n && i < 8; ++i)
            accum[i] = 0.0;
    }

    for (int it = 1; it <= g; ++it) {
        double tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int err = a6;
        a2(a1, &x, tmp, &err);
        for (int i = 0; i < n && i < 8; ++i)
            accum[i] += tmp[i];
        x += dx;
    }

    b37_a1ab0_state = 2 * g;


    for (int i = 0; i < n && i < 8; ++i) {
        double v = ((a5 - a4) * accum[i]) / (double)g + a7[i];
        a7[i] = v * 0.5;
    }

    return (n <= 0) ? (long long)(2 * g) : 0;
}
