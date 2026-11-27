










#pragma once




namespace UGS
{
namespace Math
{

struct Vector3
{
    double x, y, z;
};

struct TransformMatrix
{
    double m[16];
};

}
}



int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


void __cdecl ARC_SPLINE_transform_vec_3d(UGS::Math::Vector3* p,
                                         UGS::Math::TransformMatrix* mat,
                                         bool normalize,
                                         UGS::Math::Vector3* out)
{
    const double* m = mat->m;
    UGS::Math::Vector3 tmp;
    tmp.x = p->y * m[4] + p->x * m[0] + p->z * m[8];
    tmp.y = p->x * m[1] + p->y * m[5] + p->z * m[9];
    tmp.z = p->x * m[2] + p->y * m[6] + p->z * m[10];
    *out = tmp;
    if (normalize)
    {
        double len;
        VEC3_unitize(out, 1.0e-10, &len, out);
    }
}
