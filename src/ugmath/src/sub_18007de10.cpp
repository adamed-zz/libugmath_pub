









#include <cmath>



extern "C" char sub_18007C440(double* out, const double* A, long long p, long long q);

extern "C" __declspec(noinline) char sub_18007DE10(const double* A, long long p, long long q,
                                                   double* out, double* tmp) {
    const double kDblMin = 2.2250738585072014e-308;
    double g00 = A[3 * p];
    double g01 = A[p + 2 * q];
    double g10 = A[q + 2 * p];
    double g11 = A[3 * q];
    double b[4] = {g00, g01, g10, g11};
    double T;
    double S;
    if (std::fabs(g10 - g01) < kDblMin) {
        T = 1.0;
        S = 0.0;
    } else {
        double t = (g00 + g11) / (g10 - g01);
        double root = std::sqrt(t * t + 1.0);
        T = t / root;
        S = 1.0 / root;
        if (!(T == 1.0 && S == 0.0)) {
            b[0] = g10 * S + T * g00;
            b[1] = T * g10 - S * g00;
            b[2] = g11 * S + T * g01;
            b[3] = T * g11 - g01 * S;
        }
    }
    char result = sub_18007C440(tmp, b, 0, 1);
    double o0 = tmp[0];
    double no1 = -tmp[1];
    out[0] = T * o0 - S * no1;
    out[1] = T * no1 + S * o0;
    return result;
}
