






#include <math.h>

extern "C" double* sub_1800548F0(int n, const double* pts, const double* center, double off,
                                 double* maxout, double* meanout) {
    double sum = 0.0;
    *maxout = 0.0;
    for (int i = 0; i < n; ++i) {
        const double dx = pts[3 * i] - center[0];
        const double dy = pts[3 * i + 1] - center[1];
        const double dz = pts[3 * i + 2] - center[2];
        const double v = fabs(sqrt(dx * dx + dy * dy + dz * dz) - off);
        sum += v;
        if (v > *maxout) *maxout = v;
    }
    *meanout = sum / (double)n;
    return meanout;
}
