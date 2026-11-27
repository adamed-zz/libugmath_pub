










#include <cmath>

namespace UGS {
namespace Math {

struct Vector3 {
    double X;
    double Y;
    double Z;
};

namespace PointCloudUtils {

bool IsCollinear(const Vector3& a, const Vector3& b) {








    const double na = std::sqrt(a.X * a.X + a.Y * a.Y + a.Z * a.Z);
    const double nb = std::sqrt(b.X * b.X + b.Y * b.Y + b.Z * b.Z);
    const double m = (na > nb) ? na : nb;
    double r11;
    double r22;
    if (m == 0.0) {
        r11 = a.X;
        r22 = b.Y;
    } else {
        const double c0 = a.Y * b.Z - a.Z * b.Y;
        const double c1 = a.Z * b.X - a.X * b.Z;
        const double c2 = a.X * b.Y - a.Y * b.X;
        const double nc = std::sqrt(c0 * c0 + c1 * c1 + c2 * c2);
        r11 = m;
        r22 = nc / m;
    }
    const double tol = std::fabs(r11) * 1.0e-10;
    int cnt = 0;
    if (std::fabs(r11) > tol) ++cnt;
    if (std::fabs(r22) > tol) ++cnt;
    return cnt <= 1;
}

}
}
}
