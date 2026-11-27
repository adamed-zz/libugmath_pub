





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



int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


void __cdecl ARC_SPLINE_adjust_vec_on_pln(bool unitize,
                                          UGS::Math::Vector3* n,
                                          UGS::Math::Vector3* v)
{
    const double t = -(v->x * n->x + v->y * n->y + v->z * n->z);
    UGS::Math::Vector3 tmp;
    tmp.x = n->x * t + v->x;
    tmp.y = n->y * t + v->y;
    tmp.z = n->z * t + v->z;
    *v = tmp;
    if (unitize)
    {
        double len;
        VEC3_unitize(v, 1.0e-10, &len, v);
    }
}
