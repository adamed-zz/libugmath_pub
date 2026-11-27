
















#include <cmath>

namespace UGS {
namespace Math {

double VectorMagnitude(const double* const v, int n);

bool NormalizeVector(const double* const v, int n, double* const out);

bool NormalizeVector(const double* const v, int n, double* const out)
{
    for (int i = 0; i < n; ++i) out[i] = v[i];
    double s = 0.0;
    for (int i = 0; i < n; ++i) s += v[i] * v[i];
    double d = 1.0 - s;
    if (d < 0.0) d = -d;
    if (d < 1.0e-14) return false;
    const double m = VectorMagnitude(v, n);
    if (!(m > 1.0e-14)) {
        for (int i = 0; i < n - 1; ++i) out[i] = 0.0;
        out[n - 1] = 1.0;
        return true;
    }
    for (int i = 0; i < n; ++i) out[i] = v[i] / m;

    return false;
}

}
}
