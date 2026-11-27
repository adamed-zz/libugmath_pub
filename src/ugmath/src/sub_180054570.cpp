













#include <math.h>

extern "C" double* sub_180054570(int n, const double* pts, const double* p0, const double* dir,
                                 double* maxout, double* meanout) {
    double sum = 0.0;
    *maxout = 0.0;
    const double px = p0[0];
    const double py = p0[1];
    const double pz = p0[2];
    const double dx = dir[0];
    const double dy = dir[1];
    const double dz = dir[2];
    for (int i = 0; i < n; ++i) {
        const double len = sqrt(dy * dy + dx * dx + dz * dz);
        const double v = fabs(((pts[3 * i + 1] - py) * dy + (pts[3 * i] - px) * dx +
                               (pts[3 * i + 2] - pz) * dz) /
                              len);
        sum += v;
        if (v > *maxout) *maxout = v;
    }
    *meanout = sum / (double)n;
    return meanout;
}
