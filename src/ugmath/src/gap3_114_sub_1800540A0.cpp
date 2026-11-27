






#include <math.h>

extern "C" double* sub_1800540A0(int n, const double* pts, const double* center, double off,
                                 double* maxout, double* meanout) {
    double sum = 0.0;
    *maxout = 0.0;
    for (int i = 0; i < n; ++i) {
        const double dy = pts[2 * i + 1] - center[1];
        const double dx = pts[2 * i] - center[0];
        const double d = fabs(sqrt(dx * dx + dy * dy) - off);
        sum += d;
        if (d > *maxout) *maxout = d;
    }
    *meanout = sum / (double)n;
    return meanout;
}
