
#include <cmath>

#include "types.h"

using UGS::Math::Vector3;

#define VEC3_is_finite(u) \
    (fabs((u)->x) < 1.0e19 && fabs((u)->y) < 1.0e19 && fabs((u)->z) < 1.0e19)
#define MACH_ASSERT(expr)                                    \
    if (MACH__checking_level > 0 && !(expr))                 \
    ERROR_assertion_failed(__FILE__, __LINE__, "%s", #expr)




static __forceinline int vec3_unitize_inline(const Vector3* u, double tolerance,
                                             double* len_out, Vector3* out)
{
#line 84 "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\vec3.c"
    MACH_ASSERT(VEC3_is_finite (u));

    double len_sq = u->x * u->x + u->y * u->y + u->z * u->z;
    double len = sqrt(len_sq);
    int result = !(tolerance >= len);
    if (result == 0)
    {
        *len_out = 0.0;
        out->x = 0.0;
        out->y = 0.0;
        out->z = 0.0;
    }
    else
    {
        double inv = 1.0 / len;
        *len_out = len;
        out->x = u->x * inv;
        out->y = u->y * inv;
        out->z = u->z * inv;
    }
    return result;
}

int VEC3_make_perpendicular(const Vector3* u, Vector3* v)
{
    double tol = EQ_ask_length_tolerance();
    if (tol >= sqrt(u->x * u->x + u->y * u->y + u->z * u->z))
        return 0;
    if (tol >= sqrt(v->x * v->x + v->y * v->y + v->z * v->z))
        return 0;

    Vector3 w;
    w.x = u->y * v->z - u->z * v->y;
    w.y = u->z * v->x - u->x * v->z;
    w.z = u->x * v->y - u->y * v->x;

    double x = w.y * u->z - w.z * u->y;
    double y = w.z * u->x - w.x * u->z;
    double z = w.x * u->y - w.y * u->x;
    w.x = x;
    w.y = y;
    w.z = z;

    double wlen = 0.0;
    vec3_unitize_inline(&w, EQ_ask_length_tolerance(), &wlen, &w);

    double vlen = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    Vector3 r = {w.x * vlen, w.y * vlen, w.z * vlen};
    *v = r;
    return 1;
}
