





























#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
struct TransformMatrix
{
    double m[16];
};
}
}



extern const double g_math_one;

void ARC_SPLINE_ask_householder_transformation(UGS::Math::Vector3* a1,
                                               UGS::Math::Vector3* a2,
                                               UGS::Math::TransformMatrix* a3)
{
    const double one = g_math_one;
    a3->m[0] = 1.0;
    a3->m[1] = 0.0;
    a3->m[2] = 0.0;
    a3->m[3] = 0.0;
    a3->m[4] = 0.0;
    a3->m[5] = 1.0;
    a3->m[6] = 0.0;
    a3->m[7] = 0.0;
    a3->m[8] = 0.0;
    a3->m[9] = 0.0;
    a3->m[10] = 1.0;
    a3->m[11] = 0.0;
    a3->m[12] = 0.0;
    a3->m[13] = 0.0;
    a3->m[14] = 0.0;
    a3->m[15] = 1.0;

    double vx = a2->x - a1->x * one;
    double vy = a2->y - a1->y * one;
    double vz = a2->z - a1->z * one;

    double len = sqrt(vx * vx + vy * vy + vz * vz);
    if ( len > 1.0e-10 )
    {
        double inv = one / len;
        vx *= inv;
        vy *= inv;
        vz *= inv;
        a3->m[0] = one - (vx + vx) * vx;
        a3->m[1] = 0.0 - (vy + vy) * vx;
        a3->m[2] = 0.0 - (vz + vz) * vx;
        a3->m[4] = 0.0 - (vx + vx) * vy;
        a3->m[5] = one - (vy + vy) * vy;
        a3->m[6] = 0.0 - (vz + vz) * vy;
        a3->m[8] = 0.0 - (vx + vx) * vz;
        a3->m[9] = 0.0 - (vy + vy) * vz;
        a3->m[10] = one - (vz + vz) * vz;
    }
}
