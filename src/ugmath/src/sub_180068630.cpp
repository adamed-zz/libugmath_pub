






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



int MTX3_init_x_y_z(const UGS::Math::Vector3* x, const UGS::Math::Vector3* y,
                    const UGS::Math::Vector3* z, UGS::Math::Matrix3* r);

extern "C" int sub_180068630(UGS::Math::Matrix3* m)
{

    const UGS::Math::Vector3 x = *reinterpret_cast<const UGS::Math::Vector3*>(&m->m[0]);
    const UGS::Math::Vector3 y = *reinterpret_cast<const UGS::Math::Vector3*>(&m->m[3]);
    const UGS::Math::Vector3 z = *reinterpret_cast<const UGS::Math::Vector3*>(&m->m[6]);

    const int result = MTX3_init_x_y_z(&x, &y, &z, m);
    if (!result)
    {
        if (MACH__checking_level)
            ERROR_assertion_failed(
                "o:\\nx2412\\ip1700\\src\\ugmath\\no\\ind\\Math_Box3D.cxx", 1351,
                "%s", "validMtx");
        m->m[0] = 1.0;
        m->m[1] = 0.0;
        m->m[2] = 0.0;
        m->m[3] = 0.0;
        m->m[4] = 1.0;
        m->m[5] = 0.0;
        m->m[6] = 0.0;
        m->m[7] = 0.0;
        m->m[8] = 1.0;
        return 0;
    }
    return result;
}
