







#include "b37_math.h"

#include <cmath>

namespace {

constexpr double kTol = 1.0e-10;

}

void PNT3_cartesian_to_spherical(UGS::Math::Point3* a1, UGS::Math::Point3* a2) {
    double y = a1->y;
    double x = a1->x;
    double z = a1->z;
    double r = sqrt(y * y + x * x + z * z);

    double theta;
    if (!(std::fabs(x) <= kTol)) {
        double v = std::atan(y / x) * b37c::kRadToDeg;
        if (x < 0.0) {
            v += b37c::kDeg180;
        } else if (y < 0.0) {
            v += b37c::kDeg360;
        }
        theta = v;
    } else if (!(std::fabs(y) <= kTol)) {
        theta = !(y > kTol) ? b37c::kDeg270 : b37c::kDeg90;
    } else {
        theta = 0.0;
    }

    double phi = 0.0;
    if (!(std::fabs(r) <= kTol)) {
        phi = std::acos(z / r) * b37c::kRadToDeg;
    }

    a2->x = r;
    a2->y = theta;
    a2->z = phi;
}
