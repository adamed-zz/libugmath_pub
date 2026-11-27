













#include <cmath>

extern "C" __declspec(noinline) char sub_18007C440(double* out, const double* A, long long p,
                                                   long long q) {
    const double kDblMin = 2.2250738585072014e-308;
    double x = A[p + 2 * q];
    double ax = std::fabs(x);
    if (ax + ax < kDblMin) {
        out[0] = 1.0;
        out[1] = 0.0;
        return 0;
    }
    double t = (A[3 * p] - A[3 * q]) / (ax + ax);
    double root = std::sqrt(t * t + 1.0);
    double rho;
    if (!(t > 0.0))
        rho = 1.0 / (t - root);
    else
        rho = 1.0 / (root + t);
    double sign;
    if (!(rho > 0.0))
        sign = -1.0;
    else
        sign = 1.0;
    double den = std::sqrt(rho * rho + 1.0);
    double inv = 1.0 / den;
    double c = inv;
    double s = std::fabs(rho) * (x / ax * -sign) * inv;
    out[0] = c;
    out[1] = s;
    return 1;
}
