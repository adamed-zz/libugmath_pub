











typedef unsigned long long u64;

namespace UGS {
namespace Math {

struct Point3 {
    double x, y, z;
};

struct TransformMatrix {
    double m[16];
};

}
}

#include <math.h>

void ARC_SPLINE_ask_translation_matrix(
    UGS::Math::Point3* a1,
    UGS::Math::Point3* a2,
    UGS::Math::TransformMatrix* a3)
{
    double const dx = a2->x - a1->x;
    double const dy = a2->y - a1->y;
    double const dz = a2->z - a1->z;

    u64* d = reinterpret_cast<u64*>(a3);
    d[0] = 0x3FF0000000000000ull;
    d[1] = 0;
    d[2] = 0;
    d[3] = 0;
    d[4] = 0;
    d[5] = 0x3FF0000000000000ull;
    d[6] = 0;
    d[7] = 0;
    d[8] = 0;
    d[9] = 0;
    d[10] = 0x3FF0000000000000ull;
    d[11] = 0;
    d[12] = 0;
    d[13] = 0;
    d[14] = 0;
    d[15] = 0x3FF0000000000000ull;

    double const ex = a1->x - a2->x;
    double const ey = a1->y - a2->y;
    double const ez = a1->z - a2->z;

    if (sqrt(ex * ex + ey * ey + ez * ez) > 1.0e-10)
    {
        a3->m[12] = dx;
        a3->m[13] = dy;
        a3->m[14] = dz;
    }
}
