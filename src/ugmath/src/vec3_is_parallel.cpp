

















namespace UGS
{
namespace Math
{
struct Vector3
{
    double x, y, z;
};
}
}



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);


bool VEC3_is_parallel(const UGS::Math::Vector3* u,
                      const UGS::Math::Vector3* v, double tolerance);


#include <math.h>

#define MACH_ASSERT(expr)                                     \
    if (MACH__checking_level > 0 && !(expr))                  \
        ERROR_assertion_failed(__FILE__, __LINE__, "%s", #expr)


#define VEC3_is_finite(u)                                     \
    (fabs((u)->x) < 1.0e19 && fabs((u)->y) < 1.0e19 &&        \
     fabs((u)->z) < 1.0e19)

bool VEC3_is_parallel(const UGS::Math::Vector3* u,
                      const UGS::Math::Vector3* v, double tolerance)
{
#line 128 "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\vec3.c"
    MACH_ASSERT(VEC3_is_finite( u ));
    MACH_ASSERT(VEC3_is_finite( v ));

    double u_len_sq = u->x * u->x + u->y * u->y + u->z * u->z;
    if (1.0e-10 >= sqrt(u_len_sq))
        return true;

    double v_len_sq = v->x * v->x + v->y * v->y + v->z * v->z;
    if (1.0e-10 >= sqrt(v_len_sq))
        return true;


    double cross_x = v->z * u->y - v->y * u->z;
    double cross_y = v->x * u->z - v->z * u->x;
    double cross_z = v->y * u->x - v->x * u->y;

    double sin_sq = (cross_x * cross_x + cross_y * cross_y +
                     cross_z * cross_z) /
                    (v_len_sq * u_len_sq);
    if (tolerance * tolerance >= fabs(sin_sq))
        return true;
    return false;
}
