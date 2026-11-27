







#include "b37_math.h"

#include <cmath>

PNT3_colinear_condition_t PNT3_colinear_condition(const UGS::Math::Point3* a1,
                                                  const UGS::Math::Point3* a2,
                                                  const UGS::Math::Point3* a3, double a4) {
    if (!PNT3_is_colinear(a1, a2, a3, a4))
        return PNT3_CC_NOT_COLINEAR;

    double d13y = a1->y - a3->y;
    double d13x = a1->x - a3->x;
    double d13z = a1->z - a3->z;
    double d13_sq = d13y * d13y + d13x * d13x;
    d13_sq += d13z * d13z;
    if (a4 >= sqrt(d13_sq))
        return PNT3_CC_P3_EQ_P1;

    double d23z = a2->z - a3->z;
    double d23x = a2->x - a3->x;
    double d23y = a2->y - a3->y;
    double d23_sq = d23y * d23y + d23x * d23x;
    d23_sq += d23z * d23z;
    if (a4 >= sqrt(d23_sq))
        return PNT3_CC_P3_EQ_P2;

    double d12x = a1->x - a2->x;
    double d12y = a1->y - a2->y;
    double d12z = a1->z - a2->z;
    double d12_sq = d12y * d12y + d12x * d12x;
    d12_sq += d12z * d12z;

    double d31y = a3->y - a1->y;
    double d31x = a3->x - a1->x;
    double d31z = a3->z - a1->z;
    double d31_sq = d31y * d31y + d31x * d31x;
    d31_sq += d31z * d31z;

    double d32y = a3->y - a2->y;
    double d32x = a3->x - a2->x;
    double d32z = a3->z - a2->z;
    double d32_sq = d32y * d32y + d32x * d32x;
    d32_sq += d32z * d32z;

    if (d12_sq > d31_sq && d12_sq > d32_sq)
        return PNT3_CC_P1P2_LONGEST;
    if (d32_sq > d31_sq)
        return PNT3_CC_P2_INSIDE;
    return PNT3_CC_P1P3_LONGEST;
}
