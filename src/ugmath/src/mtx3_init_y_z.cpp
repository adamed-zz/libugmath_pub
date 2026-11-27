











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



__declspec(dllimport) extern int MACH__checking_level;
__declspec(dllimport) void ERROR_assertion_failed(const char* file, int line,
                                                  const char* fmt, ...);



int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);

bool MTX3_is_ortho_normal(const UGS::Math::Matrix3* m, double tolerance);


#include <math.h>


static __forceinline UGS::Math::Vector3 cross3(const UGS::Math::Vector3* a,
                                               const UGS::Math::Vector3* b)
{
    return UGS::Math::Vector3{a->y * b->z - a->z * b->y,
                              a->z * b->x - a->x * b->z,
                              a->x * b->y - a->y * b->x};
}

int MTX3_init_y_z(const UGS::Math::Vector3* a1, const UGS::Math::Vector3* a2,
                  UGS::Math::Matrix3* a3)
{
    const double tol = 1.0e-10;
    UGS::Math::Vector3 u1 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 u2 = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 x;
    double len;

    if (!VEC3_unitize(a1, tol, &len, &u1))
        return 0;
    if (!VEC3_unitize(a2, tol, &len, &u2))
        return 0;

    if (!(tol >= fabs(u2.y * u1.y + u2.x * u1.x + u2.z * u1.z)))
        return 0;

    x = cross3(&u1, &u2);
    VEC3_unitize(&x, tol, &len, &x);

    a3->m[0] = x.x;
    a3->m[1] = x.y;
    a3->m[2] = x.z;
    a3->m[6] = u2.x;
    a3->m[7] = u2.y;
    a3->m[8] = u2.z;

    u1 = cross3(&u2, &x);
    a3->m[3] = u1.x;
    a3->m[4] = u1.y;
    a3->m[5] = u1.z;

    if (MACH__checking_level && !MTX3_is_ortho_normal(a3, 1.0e-14))
        ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c",
                               540, "%s", "MTX3_is_ortho_normal (r)");
    return 1;
}
