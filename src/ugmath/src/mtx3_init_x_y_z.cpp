



#pragma once


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

int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* r)
{
    const double tol = 1.0e-10;
    UGS::Math::Vector3 t;
    UGS::Math::Vector3 vx = {0.0, 0.0, 0.0};
    double len;
    UGS::Math::Vector3 vy = {0.0, 0.0, 0.0};
    UGS::Math::Vector3 vz = {0.0, 0.0, 0.0};
    int ok = 0;

    if (VEC3_unitize(x, tol, &len, &vx) && VEC3_unitize(y, tol, &len, &vy) &&
        VEC3_unitize(z, tol, &len, &vz) &&
        tol >= fabs(vy.y * vx.y + vy.x * vx.x + vy.z * vx.z) &&
        tol >= fabs(vz.y * vx.y + vz.x * vx.x + vz.z * vx.z) &&
        tol >= fabs(vz.y * vy.y + vz.x * vy.x + vz.z * vy.z))
    {
        ok = 1;
        t.x = vx.y * vy.z - vx.z * vy.y;
        t.y = vx.z * vy.x - vx.x * vy.z;
        t.z = vx.x * vy.y - vx.y * vy.x;
        VEC3_unitize(&t, tol, &len, &t);
        if (t.y * vz.y + t.x * vz.x + t.z * vz.z < 0.0)
        {
            t.x *= -1.0;
            t.y *= -1.0;
            t.z *= -1.0;
        }
        vz.x = t.x;
        vz.y = t.y;
        vz.z = t.z;
        double m3 = vz.y * vx.z - vz.z * vx.y;
        double m4 = vz.z * vx.x - vz.x * vx.z;
        double m5 = vz.x * vx.y - vz.y * vx.x;
        if (m4 * vy.y + m3 * vy.x + m5 * vy.z < 0.0)
        {
            m3 *= -1.0;
            m4 *= -1.0;
            m5 *= -1.0;
        }
        r->m[0] = vx.x;
        r->m[1] = vx.y;
        r->m[2] = vx.z;
        r->m[3] = m3;
        r->m[4] = m4;
        r->m[5] = m5;
        r->m[6] = vz.x;
        r->m[7] = vz.y;
        r->m[8] = vz.z;
        vy.x = m3;
        vy.y = m4;
        vy.z = m5;
        if (MACH__checking_level && !MTX3_is_ortho_normal(r, 1.0e-14))
            ERROR_assertion_failed("o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\mtx3.c",
                                   540, "%s", "MTX3_is_ortho_normal (r)");
    }
    return ok;
}
