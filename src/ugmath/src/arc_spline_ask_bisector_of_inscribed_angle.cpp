



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
struct Matrix3
{
    double m[9];
};
}
}



struct PLN3_s
{
    double origin[3];
    double normal[3];
};


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);



void ARC_SPLINE_ask_inscribed_angle_and_type(UGS::Math::Vector3* a1,
                                             UGS::Math::Vector3* a2,
                                             UGS::Math::Vector3* a3, int a4,
                                             double a5, double* a6, double* a7,
                                             int* a8);



void MTX3_rot_about_axis(double angle, const UGS::Math::Vector3* axis,
                         UGS::Math::Matrix3* matrix);


void ARC_SPLINE_ask_bisector_of_inscribed_angle(
    UGS::Math::Vector3* a1, UGS::Math::Vector3* a2, UGS::Math::Point3* a3,
    UGS::Math::Vector3* a4, double a5, double* a6, double* a7, int* a8,
    UGS::Math::Vector3* a9, PLN3_s* a10);














void ARC_SPLINE_ask_bisector_of_inscribed_angle(
    UGS::Math::Vector3* a1,
    UGS::Math::Vector3* a2,
    UGS::Math::Point3* a3,
    UGS::Math::Vector3* a4,
    double a5,
    double* a6,
    double* a7,
    int* a8,
    UGS::Math::Vector3* a9,
    PLN3_s* a10)
{
    *a6 = 0.0;
    *a7 = 0.0;
    *a8 = -2;

    UGS::Math::Matrix3 rot = {1.0, 0.0, 0.0,
                              0.0, 1.0, 0.0,
                              0.0, 0.0, 1.0};

    double len, len2;
    double nz = 1.0;
    UGS::Math::Vector3 n;
    if (a4)
    {
        n.x = a4->x;
        n.y = a4->y;
        n.z = a4->z;
        VEC3_unitize(&n, 1.0e-10, &len, &n);
        nz = n.z;
    }
    else
    {
        n.x = 0.0;
        n.y = 0.0;
        n.z = 1.0;
    }

    UGS::Math::Vector3 w = *a2;

    double d1 = -(a1->y * n.y + a1->x * n.x + a1->z * nz);
    UGS::Math::Vector3 u;
    u.y = d1 * n.y + a1->y;
    u.x = d1 * n.x + a1->x;
    u.z = d1 * nz + a1->z;
    VEC3_unitize(&u, 1.0e-10, &len2, &u);

    double d2 = -(w.y * n.y + w.x * n.x + w.z * n.z);



    w.y = d2 * n.y + a2->y;
    w.x = d2 * n.x + a2->x;
    w.z = d2 * n.z + a2->z;
    VEC3_unitize(&w, 1.0e-10, &len2, &w);

    ARC_SPLINE_ask_inscribed_angle_and_type(&u, &w, &n, 0, a5, a6, a7, a8);

    MTX3_rot_about_axis(*a6 * 0.008726646259971641, &n, &rot);

    a9->x = rot.m[3] * u.y + rot.m[0] * u.x + rot.m[6] * u.z;
    a9->y = rot.m[4] * u.y + rot.m[1] * u.x + rot.m[7] * u.z;
    a9->z = rot.m[5] * u.y + rot.m[2] * u.x + rot.m[8] * u.z;
    VEC3_unitize(a9, 1.0e-10, &len, a9);

    a10->origin[0] = a3->x;
    a10->origin[1] = a3->y;
    a10->origin[2] = a3->z;

    UGS::Math::Vector3 nrm;
    nrm.x = a9->y * n.z - a9->z * n.y;
    nrm.y = a9->z * n.x - a9->x * n.z;
    nrm.z = a9->x * n.y - a9->y * n.x;
    *(UGS::Math::Vector3*)a10->normal = nrm;
    VEC3_unitize((UGS::Math::Vector3*)a10->normal, 1.0e-10, &len,
                 (UGS::Math::Vector3*)a10->normal);
}
