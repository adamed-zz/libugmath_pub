







#include "ugmath/box3d.h"


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out, UGS::Math::Vector3* out);
bool VEC3_is_parallel(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v, double tolerance);

namespace UGS {
namespace Math {

bool Box3D::IsBoxAligned(const Box3D& other) const {
    const Vector3* o0 = (const Vector3*)&other.matrix[0];
    const Vector3* o1 = (const Vector3*)&other.matrix[3];
    const Vector3* x = (const Vector3*)&matrix[0];
    const Vector3* y = (const Vector3*)&matrix[3];
    const Vector3* z = (const Vector3*)&matrix[6];
    if (!VEC3_is_parallel(o0, x, 1.0e-10) &&
        !VEC3_is_parallel(o0, y, 1.0e-10) &&
        !VEC3_is_parallel(o0, z, 1.0e-10))
        return false;
    return VEC3_is_parallel(o1, y, 1.0e-10) ||
           VEC3_is_parallel(o1, x, 1.0e-10) ||
           VEC3_is_parallel(o1, z, 1.0e-10);
}

}
}
