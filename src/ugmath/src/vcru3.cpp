


#include "ugmath/vector3.h"
#include "ugmath/tolerance.h"
#include "ugmath/vec3_ops.h"

using UGS::Math::Vector3;

void vcru3(const double* u, const double* v, int* flag, double* out)
{
    double u0 = u[0];
    double u1 = u[1];
    double u2 = u[2];
    double v0 = v[0];
    double v1 = v[1];
    double v2 = v[2];

    Vector3 n;
    n.x = u1 * v2 - u2 * v1;
    n.y = v0 * u2 - u0 * v2;
    n.z = u0 * v1 - v0 * u1;

    double len;
    *flag = VEC3_unitize(&n, EQ_ask_length_tolerance(), &len,
                         reinterpret_cast<Vector3*>(out))
                ? 1
                : 0;
}
