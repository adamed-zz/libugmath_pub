





#include "b37_math.h"

#include <cmath>

namespace {

constexpr double kTol = 1.0e-10;

}

void PNT3_cartesian_to_cylindrical(UGS::Math::Point3* a1, UGS::Math::Point3* a2) {
    double y = a1->y;
    double x = a1->x;
    double r = sqrt(y * y + x * x);

    double angle;
    if (!(std::fabs(x) <= kTol)) {
        double v = std::atan(y / x) * b37c::kRadToDeg;
        if (x < 0.0) {
            v += b37c::kDeg180;
        } else if (y < 0.0) {
            v += b37c::kDeg360;
        }
        angle = v;
    } else if (!(std::fabs(y) <= kTol)) {
        angle = !(y > kTol) ? b37c::kDeg270 : b37c::kDeg90;
    } else {
        angle = 0.0;
    }

    double z = a1->z;

    a2->x = r;
    a2->z = z;
    a2->y = angle;
}
