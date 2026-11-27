#include "ugmath/vec3.h"

#include <cmath>

namespace ugmath {

double length(const Vec3& v) {
    return std::sqrt(lengthSquared(v));
}

Vec3 normalized(const Vec3& v, double eps) {
    const double len = length(v);

    if (!(len > eps)) {
        return Vec3();
    }
    return v / len;
}

bool normalize(Vec3& v, double eps) {
    const double len = length(v);
    if (!(len > eps)) {
        return false;
    }
    v /= len;
    return true;
}

bool approxEquals(const Vec3& a, const Vec3& b, double eps) {
    return std::fabs(a.x - b.x) <= eps
        && std::fabs(a.y - b.y) <= eps
        && std::fabs(a.z - b.z) <= eps;
}

}
