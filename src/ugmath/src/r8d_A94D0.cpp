


#include <math.h>

extern "C" double sub_1800A94D0(const double* p) {
    double v1 = fabs(p[1]);
    double v2 = fabs(p[0]);
    if (fabs(v2) <= 0.0) return v1;
    if (fabs(v1) <= 0.0) return v2;
    if (!(v2 > v1)) {
        const double t = v2 / v1;
        return sqrt(t * t + 1.0) * v1;
    }
    const double t = v1 / v2;
    return sqrt(t * t + 1.0) * v2;
}
