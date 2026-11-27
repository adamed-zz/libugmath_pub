






















#pragma once


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



struct ARC_SPLINE_monge_plane_s
{
    UGS::Math::Vector3 pm;
    double             d;
    unsigned char   flag;
};



int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


#include <intrin.h>

#pragma warning(push)
#pragma warning(disable : 4996)
void ARC_SPLINE_normalize_monge_plane(ARC_SPLINE_monge_plane_s* a1)
{
    *((volatile unsigned char*)&a1->flag) = 1;
    _ReadWriteBarrier();
    UGS::Math::Vector3 v;
    v.x = a1->pm.x;
    v.y = a1->pm.y;
    v.z = a1->pm.z;
    double scale;
    VEC3_unitize(&v, 1.0e-10, &scale, &v);
    a1->d /= scale;
    a1->pm.x = v.x;
    a1->pm.y = v.y;
    a1->pm.z = v.z;
}
#pragma warning(pop)
