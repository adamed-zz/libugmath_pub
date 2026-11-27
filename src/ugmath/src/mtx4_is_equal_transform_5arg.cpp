












#include <cmath>
#include <cstring>

namespace UGS {
namespace Math {


struct TransformMatrix
{
    double m[16];
};


struct Matrix3
{
    double m[9];
};

}
}



extern bool MTX3_is_equal(const UGS::Math::Matrix3 *a1,
                          const UGS::Math::Matrix3 *a2,
                          double tol);

bool MTX4_is_equal_transform(const UGS::Math::TransformMatrix *a1,
                             const UGS::Math::TransformMatrix *a2,
                             double a3,
                             double a4,
                             double a5)
{
    if (!(a5 >= fabs(a1->m[15] - a2->m[15])))
        return false;

    double dx = a1->m[3] - a2->m[3];
    double dy = a1->m[7] - a2->m[7];
    double dz = a1->m[11] - a2->m[11];
    if (!(a4 >= sqrt(dx * dx + dy * dy + dz * dz)))
        return false;

    UGS::Math::Matrix3 ma, mb;
    memcpy(&ma.m[0], &a1->m[0], 3 * sizeof(double));
    memcpy(&ma.m[3], &a1->m[4], 3 * sizeof(double));
    memcpy(&ma.m[6], &a1->m[8], 3 * sizeof(double));
    memcpy(&mb.m[0], &a2->m[0], 3 * sizeof(double));
    memcpy(&mb.m[3], &a2->m[4], 3 * sizeof(double));
    memcpy(&mb.m[6], &a2->m[8], 3 * sizeof(double));
    return MTX3_is_equal(&ma, &mb, a3);
}
