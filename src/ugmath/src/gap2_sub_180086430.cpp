












#include <cmath>
#include <cstdint>
#include <cstring>
#include <utility>

namespace {

struct Vec3 {
    double x, y, z;
};

}

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
};

struct TransformMatrix {
    double M[16];
};

namespace PointCloudUtils {

TransformMatrix GetAxisTransform(const std::pair<Point3, Point3>& a, const std::pair<Point3, Point3>& b);

TransformMatrix GetAxisTransform(const std::pair<Point3, Point3>& a, const std::pair<Point3, Point3>& b) {
    TransformMatrix out;
    double* m = out.M;

    double dp0 = a.second.x - a.first.x;
    double dp1 = a.second.y - a.first.y;
    double dp2 = a.second.z - a.first.z;
    double dq0 = b.second.x - b.first.x;
    double dq1 = b.second.y - b.first.y;
    double dq2 = b.second.z - b.first.z;

    const double np = std::sqrt(dp1 * dp1 + dp0 * dp0 + dp2 * dp2);
    const double nq = std::sqrt(dq1 * dq1 + dq0 * dq0 + dq2 * dq2);
    bool ok = !(np <= 1.0e-8) && !(nq <= 1.0e-8);
    if (ok) {
        if (np != 0.0) {
            dp0 /= np;
            dp1 /= np;
            dp2 /= np;
        }
        if (nq != 0.0) {
            dq0 /= nq;
            dq1 /= nq;
            dq2 /= nq;
        }
        ok = std::fabs(dp1 * dq1 + dq0 * dp0 + dq2 * dp2) <= 1.0e-10;
    }

    if (!ok) {

        static const double kIdentity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        std::memcpy(m, kIdentity, sizeof kIdentity);
        return out;
    }

    const double t = ((b.first.y - a.first.y) * dp1 + (b.first.x - a.first.x) * dp0) +
                     (b.first.z - a.first.z) * dp2;
    m[0] = dp0;
    m[1] = dq0;
    m[2] = dp1 * dq2 - dp2 * dq1;
    m[3] = t * dp0 + a.first.x;
    m[4] = dp1;
    m[5] = dq1;
    m[6] = dp2 * dq0 - dq2 * dp0;
    m[7] = t * dp1 + a.first.y;
    m[8] = dp2;
    m[9] = dq2;
    m[10] = dq1 * dp0 - dp1 * dq0;
    m[11] = t * dp2 + a.first.z;
    m[12] = 0.0;
    m[13] = 0.0;
    m[14] = 0.0;
    m[15] = 1.0;
    return out;
}

}
}
}
