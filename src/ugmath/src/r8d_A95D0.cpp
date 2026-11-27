


#include <math.h>

extern "C" double* sub_1800A95D0(double* out, const double* z) {
    const double x = z[0];
    const double y = z[1];
    const double ax = fabs(x);
    const double ay = fabs(y);
    if (!(0.0 >= ax) || !(0.0 >= ay)) {
        double w;
        if (!(ax >= ay)) {
            const double r = ax / ay;
            w = (sqrt(r * r + 1.0) + r) * 0.5 * ay;
        } else {
            const double r = ay / ax;
            w = (sqrt(r * r + 1.0) + 1.0) * 0.5 * ax;
        }
        const double v = sqrt(w);
        if (!(x >= 0.0)) {
            const double im = (!(y >= 0.0)) ? -v : v;
            out[1] = im;
            out[0] = y / (im + im);
        } else {
            out[1] = y / (v + v);
            out[0] = v;
        }
    } else {
        out[1] = 0.0;
        out[0] = 0.0;
    }
    return out;
}
