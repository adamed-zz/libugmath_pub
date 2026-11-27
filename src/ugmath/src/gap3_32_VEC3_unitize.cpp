












#include "types.h"

#include <math.h>

int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out)
{
    if (MACH__checking_level > 0 &&
        !(fabs(u->x) < 1.0e19 && fabs(u->y) < 1.0e19 && fabs(u->z) < 1.0e19))
        ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\vec3.c",
                               84, "%s", "VEC3_is_finite (u)");
    double len = sqrt(u->x * u->x + u->y * u->y + u->z * u->z);
    int ok = !(tol >= len);
    if (ok)
    {
        *len_out = len;
        double inv = 1.0 / len;
        UGS::Math::Vector3 v;
        v.x = u->x * inv;
        v.y = u->y * inv;
        v.z = u->z * inv;
        *out = v;
    }
    else
    {
        *len_out = 0.0;
        out->x = out->y = out->z = 0.0;
    }
    return ok;
}
