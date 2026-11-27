








#include "b37_math.h"

#include <cmath>

void PNT3_spherical_to_cartesian(UGS::Math::Point3* a1, UGS::Math::Point3* a2) {
    double theta = a1->y / b37c::kRadToDeg;
    double phi = a1->z / b37c::kRadToDeg;
    double r = a1->x;
    double sin_phi = std::sin(phi);

    a2->x = std::cos(theta) * r * sin_phi;
    a2->y = std::sin(theta) * r * sin_phi;
    a2->z = std::cos(phi) * r;
}
