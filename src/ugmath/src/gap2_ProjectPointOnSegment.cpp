
















#include <cmath>

namespace UGS {
namespace Math {

double VectorMagnitude(const double* const v, int n);

void ProjectPointOnSegment(const double* const p, const double* const a,
                           const double* const b, double* const out, double& t);

void ProjectPointOnSegment(const double* const p, const double* const a,
                           const double* const b, double* const out, double& t)
{
    t = 0.0;
    out[0] = 0.0;
    out[1] = 0.0;
    out[2] = 0.0;


    const double dx = a[0] - p[0];
    const double dy = a[1] - p[1];
    const double dz = a[2] - p[2];
    const double v[3] = {dx, dy, dz};
    const double m = VectorMagnitude(v, 3);
    if (!(9.999999974752427e-07 > m)) {
        const double len2 = m * m;
        const double raw = ((b[1] - p[1]) * dy + (b[0] - p[0]) * dx +
                            (b[2] - p[2]) * dz) / len2;
        double tt = 0.0;


        if (!(raw <= 0.0)) tt = raw < 1.0 ? raw : (raw != raw ? raw : 1.0);
        t = tt;
        out[0] = tt * dx + p[0];
        out[1] = dy * t + p[1];
        out[2] = dz * t + p[2];
    } else {
        t = 0.0;
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
    }
}

}
}
