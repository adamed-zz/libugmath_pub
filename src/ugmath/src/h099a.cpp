



#include <intrin.h>

namespace UGS {
namespace Math {
struct Vector3 {
    double x, y, z;
};
}
}

int VEC3_unitize(const UGS::Math::Vector3* v, double tol, double* len,
                 UGS::Math::Vector3* out);

void h099a(double* a1, double a2, double* a3)
{
    double v3 = a1[1];
    if (!(v3 >= 0.0))
        v3 = -v3;
    double v4 = 0.0;
    const double* v7;
    if (v3 > 0.9) {
        *a3 = 0.0;
        v7 = a1 + 1;
        v4 = a1[2];
    } else {
        *a3 = a1[2];
        v7 = a1;
    }
    a3[1] = v4;
    a3[2] = -*v7;
    double len;
    VEC3_unitize(reinterpret_cast<const UGS::Math::Vector3*>(a3), a2, &len,
                 reinterpret_cast<UGS::Math::Vector3*>(a3));
    const double x = a1[0];
    a3[6] = x;
    const double y = a1[1];
    a3[7] = y;
    const double z = a1[2];
    a3[8] = z;
    _ReadWriteBarrier();
    const double u2 = a3[2];
    const double u1 = a3[1];
    const double u0 = a3[0];
    a3[3] = u2 * y - u1 * z;
    a3[4] = u0 * z - u2 * x;
    a3[5] = u1 * x - u0 * y;
}
