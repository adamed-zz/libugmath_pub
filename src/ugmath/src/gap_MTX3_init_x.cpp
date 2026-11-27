















#include "b36_math.h"

int MTX3_init_x(const UGS::Math::Vector3* a1, UGS::Math::Matrix3* a2) {
    UGS::Math::Vector3 r = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 s = {0.0, 0.0, 0.0};
    double len = 0.0;
    if (!VEC3_unitize(a1, 1.0e-10, &len, &r)) return 0;
    VEC3_ask_perpendicular(&r, &s);
    VEC3_unitize(&s, 1.0e-10, &len, &s);
    a2->m[0] = r.x;
    a2->m[1] = r.y;
    a2->m[2] = r.z;
    a2->m[3] = s.x;
    a2->m[4] = s.y;
    a2->m[5] = s.z;
    a2->m[8] = s.y * r.x - s.x * r.y;
    a2->m[6] = s.z * r.y - s.y * r.z;
    a2->m[7] = s.x * r.z - s.z * r.x;
    if (MACH__checking_level) {
        if (!MTX3_is_ortho_normal(a2, 1.0e-14))
            ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c", 540, "%s",
                                   "MTX3_is_ortho_normal (r)");
    }
    return 1;
}
