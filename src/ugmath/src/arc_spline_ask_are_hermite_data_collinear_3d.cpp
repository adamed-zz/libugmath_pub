














#pragma once


namespace UGS
{
namespace Math
{
struct Point3
{
    double x, y, z;
};

struct Vector3
{
    double x, y, z;
};
}
}




int __cdecl VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                         UGS::Math::Vector3* out);
bool __cdecl VEC3_is_parallel(const UGS::Math::Vector3* u, const UGS::Math::Vector3* v,
                              double tolerance);

#include <math.h>

bool __cdecl ARC_SPLINE_ask_are_hermite_data_collinear_3d(
    UGS::Math::Point3* a1, UGS::Math::Vector3* a2, UGS::Math::Point3* a3,
    UGS::Math::Vector3* a4, double a5, double* a6, UGS::Math::Vector3* a7)
{
    bool collinear = false;
    double s = sin(a5 * 0.01745329251994328);
    *a7 = UGS::Math::Vector3{a3->x - a1->x, a3->y - a1->y, a3->z - a1->z};
    VEC3_unitize(a7, 1.0e-10, a6, a7);
    if (VEC3_is_parallel(a7, a2, s))
    {
        if (VEC3_is_parallel(a7, a4, s))
            collinear = true;
    }
    return collinear;
}
