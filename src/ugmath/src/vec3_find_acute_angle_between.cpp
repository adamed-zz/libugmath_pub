
























#include "ugmath/vec3_ops.h"

#include <algorithm>

double VEC3_find_acute_angle_between(const UGS::Math::Vector3* a1,
                                     const UGS::Math::Vector3* a2)
{
    double angle_between = VEC3_find_angle_between(a1, a2);
    double v3 = angle_between;
    if (angle_between > 1.5707963267948966)
        v3 = 3.141592653589793 - angle_between;
    return std::max(v3, 0.0);
}
