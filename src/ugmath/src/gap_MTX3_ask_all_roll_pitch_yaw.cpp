





















#include "b36_math.h"

namespace {
constexpr double kPi = 3.141592653589793;

double ClampAsinArg(double v) {
    if (std::fabs(v) > 0.99999999999999) return (v <= 0.0) ? -1.0 : 1.0;
    return v;
}
}

void MTX3_ask_all_roll_pitch_yaw(const UGS::Math::Matrix3* a1, int* a2,
                                 const double (&a3)[3]) {
    const double* m = a1->m;
    double pitch[2];
    double roll[4];
    double yaw[4];
    const double s = -m[6];
    if (std::fabs(s) <= 0.9999999999) {
        const double p = std::asin(s);
        const double alt = kPi - p;
        const double cp = std::cos(p);
        const double calt = std::cos(alt);
        pitch[0] = p;
        pitch[1] = alt;
        yaw[0] = std::asin(ClampAsinArg(m[3] / cp));
        yaw[1] = kPi - yaw[0];
        roll[0] = std::asin(ClampAsinArg(m[7] / cp));
        roll[1] = kPi - roll[0];
        yaw[2] = std::asin(ClampAsinArg(m[3] / calt));
        yaw[3] = kPi - yaw[2];
        roll[2] = std::asin(ClampAsinArg(m[7] / calt));
        roll[3] = kPi - roll[2];
    } else {
        pitch[0] = kPi * 0.5;
        pitch[1] = -kPi * 0.5;
        const double v7 = m[5];
        double t0;
        double t1;
        if (std::fabs(v7) <= 0.99999999999999) {
            t0 = std::asin(v7);
            t1 = t0;
        } else {
            const double sgn = (v7 <= 0.0) ? -1.0 : 1.0;
            t0 = sgn * kPi * 0.5;
            t1 = t0;
        }
        const double v12 = m[2];
        if (std::fabs(v12 - std::cos(t0)) > 1.0e-10) t0 = kPi - t0;
        double u = -t1;
        if (std::fabs(v12 - -std::cos(u)) > 1.0e-10) u = kPi - u;
        yaw[0] = 0.0;
        yaw[1] = t0;
        yaw[2] = 0.0;
        yaw[3] = u;
        roll[0] = -t0;
        roll[1] = 0.0;
        roll[2] = u;
        roll[3] = 0.0;
    }
    sub_18009CCE0(const_cast<double*>(m), pitch, roll, yaw, a2,
                  const_cast<double*>(&a3[0]));
}
