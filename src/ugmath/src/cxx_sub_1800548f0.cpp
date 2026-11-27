
struct V3 {
    double v[3];
};
#include <math.h>

extern "C" double* sub_1800548F0(int n, const double* pts, const double* center, double off,
                                 double* maxout, double* meanout) {
    double sum = 0.0;
    *maxout = 0.0;
    const double* p = pts;
    for (int i = 0; i < n; ++i) {
        const double* q = p + 3 * i;
        const double dx = q[0] - center[0];
        const double dy = q[1] - center[1];
        const double dz = q[2] - center[2];
        const double v = fabs(sqrt(dx * dx + dy * dy + dz * dz) - off);
        sum += v;
        if (v > *maxout) *maxout = v;
    }
    *meanout = sum / (double)n;
    return meanout;
}
