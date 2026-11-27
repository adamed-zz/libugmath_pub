#include "ugmath/pnt3.h"

#include <cmath>











void __cdecl PNT3_cylindrical_to_cartesian(UGS::Math::Point3* in, UGS::Math::Point3* out)
{
    double radius = in->x;
    double angle = in->y / 57.29577951308235;
    double z = in->z;

    out->x = std::cos(angle) * radius;
    out->y = std::sin(angle) * radius;
    out->z = z;
}
