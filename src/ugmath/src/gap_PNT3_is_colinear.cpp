








#include "b37_math.h"

bool PNT3_is_colinear(const UGS::Math::Point3* a1, const UGS::Math::Point3* a2,
                      const UGS::Math::Point3* a3, double a4) {
    double q2x = a2->x - a1->x;
    double q2y = a2->y - a1->y;
    double q2z = a2->z - a1->z;
    double q3x = a3->x - a2->x;
    double q3y = a3->y - a2->y;
    double q3z = a3->z - a2->z;
    double wx = a1->x - a3->x;
    double wy = a1->y - a3->y;
    double wz = a1->z - a3->z;

    double l2_q2 = q2y * q2y + q2x * q2x;
    l2_q2 += q2z * q2z;
    double l2_q3 = q3y * q3y + q3x * q3x;
    l2_q3 += q3z * q3z;
    double l2_w = wy * wy + wx * wx;
    l2_w += wz * wz;

    double m = (l2_q3 < l2_w) ? l2_q3 : l2_w;
    m = (l2_q2 < m) ? l2_q2 : m;
    bool r = a4 > m;
    if (r)
        return true;

    double dot = q3y * q2y + q3x * q2x;
    dot += q3z * q2z;
    double v = 1.0 - (dot * dot) / (l2_q3 * l2_q2);
    return a4 > v;
}
