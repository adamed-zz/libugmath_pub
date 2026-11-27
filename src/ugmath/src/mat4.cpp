#include "ugmath/mat4.h"

#include <cmath>

namespace ugmath {

Mat4 operator*(const Mat4& lhs, const Mat4& rhs) {
    Mat4 result;
    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t col = 0; col < 4; ++col) {
            double sum = 0.0;
            for (std::size_t k = 0; k < 4; ++k) {
                sum += lhs(row, k) * rhs(k, col);
            }
            result(row, col) = sum;
        }
    }
    return result;
}

Vec3 transformPoint(const Mat4& m, const Vec3& p) {
    return Vec3(
        m(0, 0) * p.x + m(0, 1) * p.y + m(0, 2) * p.z + m(0, 3),
        m(1, 0) * p.x + m(1, 1) * p.y + m(1, 2) * p.z + m(1, 3),
        m(2, 0) * p.x + m(2, 1) * p.y + m(2, 2) * p.z + m(2, 3));
}

Vec3 transformVector(const Mat4& m, const Vec3& v) {
    return Vec3(
        m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
        m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
        m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z);
}

bool approxEquals(const Mat4& a, const Mat4& b, double eps) {
    for (std::size_t i = 0; i < a.e.size(); ++i) {
        if (!(std::fabs(a.e[i] - b.e[i]) <= eps)) {
            return false;
        }
    }
    return true;
}

}
