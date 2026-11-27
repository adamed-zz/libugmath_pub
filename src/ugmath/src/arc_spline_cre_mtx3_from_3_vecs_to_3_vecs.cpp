




















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
int SOLVE_solve_3equations(double (*const a)[3], double* const b,
                           double* const x);

void ARC_SPLINE_cre_mtx3_from_3_vecs_to_3_vecs(
    UGS::Math::Vector3* a1,
    UGS::Math::Vector3* a2,
    UGS::Math::Vector3* a3,
    UGS::Math::Vector3* a4,
    UGS::Math::Vector3* a5,
    UGS::Math::Vector3* a6,
    int a7,
    UGS::Math::Matrix3* a8,
    int* a9)
{
    double len;

    *a9 = 0;

    u64* d = reinterpret_cast<u64*>(a8);
    d[0] = 0x3FF0000000000000ull;
    d[1] = 0;
    d[2] = 0;
    d[3] = 0;
    d[4] = 0x3FF0000000000000ull;
    d[5] = 0;
    d[6] = 0;
    d[7] = 0;
    d[8] = 0x3FF0000000000000ull;

    if ( a7 )
    {
        VEC3_unitize(a4, 1.0e-10, &len, a4);
        VEC3_unitize(a5, 1.0e-10, &len, a5);
        VEC3_unitize(a6, 1.0e-10, &len, a6);
        VEC3_unitize(a1, 1.0e-10, &len, a1);
        VEC3_unitize(a2, 1.0e-10, &len, a2);
        VEC3_unitize(a3, 1.0e-10, &len, a3);
    }

    double mat[3][3];
    mat[0][0] = a1->x;
    mat[0][1] = a1->y;
    mat[0][2] = a1->z;
    mat[1][0] = a2->x;
    mat[1][1] = a2->y;
    mat[1][2] = a2->z;
    mat[2][0] = a3->x;
    mat[2][1] = a3->y;
    mat[2][2] = a3->z;

    double b[3];
    double sx[3] = {0.0, 0.0, 0.0};
    double sy[3] = {0.0, 0.0, 0.0};
    double sz[3] = {0.0, 0.0, 0.0};

    b[0] = a4->x;
    b[1] = a5->x;
    b[2] = a6->x;
    if ( SOLVE_solve_3equations(mat, b, sx) )
    {
        *a9 = 1;
    }
    else
    {
        b[0] = a4->y;
        b[1] = a5->y;
        b[2] = a6->y;
        if ( SOLVE_solve_3equations(mat, b, sy) )
        {
            *a9 = 1;
        }
        else
        {
            b[0] = a4->z;
            b[1] = a5->z;
            b[2] = a6->z;
            if ( SOLVE_solve_3equations(mat, b, sz) )
            {
                *a9 = 1;
            }
            else
            {
                double* m = a8->m;
                m[0] = sx[0];
                m[3] = sx[1];
                m[6] = sx[2];
                m[1] = sy[0];
                m[4] = sy[1];
                m[7] = sy[2];
                m[2] = sz[0];
                m[5] = sz[1];
                m[8] = sz[2];
            }
        }
    }
}
