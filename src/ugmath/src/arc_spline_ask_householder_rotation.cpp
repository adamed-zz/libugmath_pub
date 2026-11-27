






















#include <math.h>

namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
struct Matrix3
{
    double m[9];
};
}
}



extern const double g_math_one;

void ARC_SPLINE_ask_householder_rotation(UGS::Math::Vector3* a1,
                                         UGS::Math::Vector3* a2,
                                         UGS::Math::Matrix3* a3)
{
    a3->m[0] = 1.0;
    a3->m[1] = 0.0;
    a3->m[2] = 0.0;
    a3->m[3] = 0.0;
    a3->m[4] = 1.0;
    a3->m[5] = 0.0;
    a3->m[6] = 0.0;
    a3->m[7] = 0.0;
    a3->m[8] = 1.0;

    double vx = a2->x - a1->x * g_math_one;
    double vy = a2->y - a1->y * g_math_one;
    double vz = a2->z - a1->z * g_math_one;

    double len = sqrt(vx * vx + vy * vy + vz * vz);
    if ( len > 1.0e-10 )
    {
        double inv = g_math_one / len;
        vx *= inv;
        vy *= inv;
        vz *= inv;
        a3->m[0] = g_math_one - (vx + vx) * vx;
        a3->m[1] = 0.0 - (vy + vy) * vx;
        a3->m[2] = 0.0 - (vz + vz) * vx;
        a3->m[3] = 0.0 - (vx + vx) * vy;
        a3->m[4] = g_math_one - (vy + vy) * vy;
        a3->m[5] = 0.0 - (vz + vz) * vy;
        a3->m[6] = 0.0 - (vx + vx) * vz;
        a3->m[7] = 0.0 - (vy + vy) * vz;
        a3->m[8] = g_math_one - (vz + vz) * vz;
    }
}
