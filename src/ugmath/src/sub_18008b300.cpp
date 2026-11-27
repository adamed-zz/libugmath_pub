











#include <math.h>

static double Len3(const double* a)
{
    double l = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    return sqrt(l);
}

extern "C" __declspec(noinline) double sub_18008B300(const double* a1, const double* a2)
{
    double u[3], v[3];
    double lu = Len3(a1);
    if (lu == 0.0) {
        u[0] = a1[0];
        u[1] = a1[1];
        u[2] = a1[2];
    } else {
        u[0] = a1[0] / lu;
        u[1] = a1[1] / lu;
        u[2] = a1[2] / lu;
    }
    double lv = Len3(a2);
    if (lv == 0.0) {
        v[0] = a2[0];
        v[1] = a2[1];
        v[2] = a2[2];
    } else {
        v[0] = a2[0] / lv;
        v[1] = a2[1] / lv;
        v[2] = a2[2] / lv;
    }
    const double ux = u[0], uy = u[1], uz = u[2];
    const double vx = v[0], vy = v[1], vz = v[2];
    const double t1 = vx * uz - ux * vz;
    const double t2 = vz * uy - uz * vy;
    const double t3 = ux * vy - vx * uy;
    const double s = t1 * t1 + t2 * t2 + t3 * t3;
    const double cross = sqrt(s);
    return atan2(cross, ux * vx + uy * vy + uz * vz);
}
