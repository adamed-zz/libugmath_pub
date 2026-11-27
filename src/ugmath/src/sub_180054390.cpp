







#include <math.h>

extern "C" double* sub_180054390(int n, const double* pts, const double* p0, const double* nrm,
                                 double* maxout, double* meanout) {
    double sum = 0.0;
    *maxout = 0.0;
    const double nx = nrm[0];
    const double ny = nrm[1];
    const double c = -(ny * p0[1] + nx * p0[0]);
    for (int i = 0; i < n; ++i) {
        const double v = fabs(ny * pts[2 * i + 1] + nx * pts[2 * i] + c);
        sum += v;
        if (v > *maxout) *maxout = v;
    }
    *meanout = sum / (double)n;
    return meanout;
}
