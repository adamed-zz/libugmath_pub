





















typedef unsigned long long u64;

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




int VEC3_unitize(UGS::Math::Vector3 const* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);
void ARC_SPLINE_cre_mtx3_from_3_vecs_to_3_vecs(UGS::Math::Vector3* a1,
                                               UGS::Math::Vector3* a2,
                                               UGS::Math::Vector3* a3,
                                               UGS::Math::Vector3* a4,
                                               UGS::Math::Vector3* a5,
                                               UGS::Math::Vector3* a6,
                                               int a7,
                                               UGS::Math::Matrix3* a8,
                                               int* a9);

#include <math.h>

void ARC_SPLINE_cre_mtx3_from_2_vecs_to_2_vecs(
    UGS::Math::Vector3* a1,
    UGS::Math::Vector3* a2,
    UGS::Math::Vector3* a3,
    UGS::Math::Vector3* a4,
    int a5,
    UGS::Math::Matrix3* a6,
    int* a7)
{
    double len;

    *a7 = 0;

    u64* d = reinterpret_cast<u64*>(a6);
    d[0] = 0x3FF0000000000000ull;
    d[1] = 0;
    d[2] = 0;
    d[3] = 0;
    d[4] = 0x3FF0000000000000ull;
    d[5] = 0;
    d[6] = 0;
    d[7] = 0;
    d[8] = 0x3FF0000000000000ull;

    if ( a5 )
    {
        VEC3_unitize(a1, 1.0e-10, &len, a1);
        VEC3_unitize(a2, 1.0e-10, &len, a2);
        VEC3_unitize(a3, 1.0e-10, &len, a3);
        VEC3_unitize(a4, 1.0e-10, &len, a4);
    }

    UGS::Math::Vector3 n1;
    UGS::Math::Vector3 n2;

    n1.x = a1->y * a2->z - a1->z * a2->y;
    n1.y = a1->z * a2->x - a1->x * a2->z;
    n1.z = a1->x * a2->y - a1->y * a2->x;

    n2.x = a3->y * a4->z - a3->z * a4->y;
    n2.y = a3->z * a4->x - a3->x * a4->z;
    n2.z = a3->x * a4->y - a3->y * a4->x;

    if ( sqrt(n2.x * n2.x + n2.y * n2.y + n2.z * n2.z) <= 1.0e-10
         || sqrt(n1.x * n1.x + n1.y * n1.y + n1.z * n1.z) <= 1.0e-10 )
    {
        *a7 = 1;
    }
    else
    {
        VEC3_unitize(&n1, 1.0e-10, &len, &n1);
        VEC3_unitize(&n2, 1.0e-10, &len, &n2);

        ARC_SPLINE_cre_mtx3_from_3_vecs_to_3_vecs(
            a1, a2, &n1, a3, a4, &n2, a5, a6, a7);
    }
}
