









__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);

#include <math.h>

namespace UGS {
namespace Math {

struct Vector3 {
    double x;
    double y;
    double z;
};

}
}




int __cdecl VEC3_ask_perpendicular(const UGS::Math::Vector3* u,
                                   UGS::Math::Vector3* v)
{
    if (MACH__checking_level > 0 &&
        !(fabs(u->x) < 1.0e19 && fabs(u->y) < 1.0e19 && fabs(u->z) < 1.0e19))
        ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\vec3.c",
                               215, "%s", "VEC3_is_finite (u)");

    double len = sqrt(u->x * u->x + u->y * u->y + u->z * u->z);
    if (len <= 1.0e-10)
    {
        v->x = v->y = v->z = 0.0;
        return 0;
    }

    double ax = fabs(u->x);
    double ay = fabs(u->y);
    double az = fabs(u->z) - 1.0e-10;
    if (ay - 1.0e-10 > ax)
    {
        if (az > ax)
        {
            v->x = 0.0;
            if (az > ay)
            {
                v->y = u->z;
                v->z = -u->y;
            }
            else
            {
                v->y = -u->z;
                v->z = u->y;
            }
            return 1;
        }
    }
    else if (az > ay)
    {
        v->y = 0.0;
        if (az > ax)
        {
            v->x = u->z;
            v->z = -u->x;
        }
        else
        {
            v->x = -u->z;
            v->z = u->x;
        }
        return 1;
    }
    v->z = 0.0;
    if (ax - 1.0e-10 > ay)
    {
        v->x = -u->y;
        v->y = u->x;
    }
    else
    {
        v->x = u->y;
        v->y = -u->x;
    }
    return 1;
}
