









































#include <math.h>




extern "C" __declspec(noinline) double sub_18008B300(const double* a1, const double* a2);

namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

struct Matrix3 {
    double m[9];
};

}
}


double EQ_ask_length_tolerance();


void MTX3_rot_about_axis(double angle, const UGS::Math::Vector3* axis,
                         UGS::Math::Matrix3* matrix);

namespace {

inline void WriteIdentity(double* out) {
    out[0] = 1.0;
    out[1] = 0.0;
    out[2] = 0.0;
    out[3] = 0.0;
    out[4] = 1.0;
    out[5] = 0.0;
    out[6] = 0.0;
    out[7] = 0.0;
    out[8] = 1.0;
}

}

extern "C" __int64 sub_18008B530(double* out, const double* u, const double* v) {
    const double tolA = EQ_ask_length_tolerance();
    const double lenA = sqrt(u[0] * u[0] + u[1] * u[1] + u[2] * u[2]);
    if (tolA >= lenA) {
        WriteIdentity(out);
        return reinterpret_cast<__int64>(out);
    }

    const double tolB = EQ_ask_length_tolerance();
    const double lenB = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (tolB >= lenB) {
        WriteIdentity(out);
        return reinterpret_cast<__int64>(out);
    }


    double uu[3];
    if (lenA == 0.0) {
        uu[0] = u[0];
        uu[1] = u[1];
        uu[2] = u[2];
    } else {
        uu[0] = u[0] / lenA;
        uu[1] = u[1] / lenA;
        uu[2] = u[2] / lenA;
    }


    double vv[3];
    if (lenB == 0.0) {
        vv[0] = v[0];
        vv[1] = v[1];
        vv[2] = v[2];
    } else {
        vv[0] = v[0] / lenB;
        vv[1] = v[1] / lenB;
        vv[2] = v[2] / lenB;
    }


    double axis[3];
    axis[0] = uu[1] * vv[2] - vv[1] * uu[2];
    axis[1] = vv[0] * uu[2] - uu[0] * vv[2];
    axis[2] = uu[0] * vv[1] - vv[0] * uu[1];


    const double crossSq = axis[1] * axis[1] + axis[0] * axis[0] + axis[2] * axis[2];
    const double crossLen = sqrt(crossSq);

    if (EQ_ask_length_tolerance() >= crossLen) {
        const double dxy = uu[0] - uu[1];
        const double dyz = uu[1] - uu[2];
        const double dzx = uu[2] - uu[0];
        if (fabs(dxy) > 1.0e-10 || fabs(dyz) > 1.0e-10) {
            const double dSq = dzx * dzx + dyz * dyz + dxy * dxy;
            double dLen = sqrt(dSq);
            double ax = dyz;
            double ay = dzx;
            double az = dxy;
            if (dLen != 0.0) {
                ax = dyz / dLen;
                ay = dzx / dLen;
                az = dxy / dLen;
            }
            axis[0] = ax;
            axis[1] = ay;
            axis[2] = az;
        } else {
            const double s = sqrt(6.0);
            axis[0] = 1.0 / s;
            axis[1] = 1.0 / s;
            axis[2] = -2.0 / s;
        }
    }

    const double angle = sub_18008B300(uu, vv);

    UGS::Math::Vector3 axisV;
    axisV.x = axis[0];
    axisV.y = axis[1];
    axisV.z = axis[2];

    UGS::Math::Matrix3 m;
    m.m[0] = 1.0;
    m.m[1] = 0.0;
    m.m[2] = 0.0;
    m.m[3] = 0.0;
    m.m[4] = 1.0;
    m.m[5] = 0.0;
    m.m[6] = 0.0;
    m.m[7] = 0.0;
    m.m[8] = 1.0;

    MTX3_rot_about_axis(angle, &axisV, &m);

    out[0] = m.m[0];
    out[1] = m.m[1];
    out[2] = m.m[2];
    out[3] = m.m[3];
    out[4] = m.m[4];
    out[5] = m.m[5];
    out[6] = m.m[6];
    out[7] = m.m[7];
    out[8] = m.m[8];
    return reinterpret_cast<__int64>(out);
}
