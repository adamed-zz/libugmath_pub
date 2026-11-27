








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


struct ARC_SPLINE_monge_plane_s
{
    UGS::Math::Vector3 pm;
    double             d;
    unsigned char   flag;
};


int VEC3_unitize(const UGS::Math::Vector3* u, double tol, double* len_out,
                 UGS::Math::Vector3* out);


extern "C" UGS::Math::Point3* sub_180001820(UGS::Math::Point3* out, double s,
                                            const UGS::Math::Point3* v);

void ARC_SPLINE_ask_pt_and_normal_of_monge_plane(ARC_SPLINE_monge_plane_s* a1,
                                                 UGS::Math::Point3* a2,
                                                 UGS::Math::Vector3* a3)
{
    a2->x = 0.0;
    a2->y = 0.0;
    a2->z = 0.0;
    a3->x = 0.0;
    a3->y = 0.0;
    a3->z = 0.0;
    a3->x = a1->pm.x;
    a3->y = a1->pm.y;
    a3->z = a1->pm.z;

    double s;
    if (!a1->flag)
    {
        double len;
        VEC3_unitize(a3, 1.0e-10, &len, a3);
        s = a1->d / len;
    }
    else
    {
        s = a1->d;
    }

    UGS::Math::Point3 v;
    v.x = a3->x;
    v.y = a3->y;
    v.z = a3->z;

    UGS::Math::Point3 tmp;
    UGS::Math::Point3* r = sub_180001820(&tmp, -s, &v);
    UGS::Math::Point3 rv = *r;
    *a2 = rv;
}
