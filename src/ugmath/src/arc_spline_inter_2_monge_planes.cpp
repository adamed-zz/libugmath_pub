









#include <cmath>


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


void ARC_SPLINE_ask_pt_and_normal_of_monge_plane(ARC_SPLINE_monge_plane_s* a1,
                                                 UGS::Math::Point3* a2,
                                                 UGS::Math::Vector3* a3);


void h634(const double* a1, const double* a2, const double* a3, const double* a4,
          int* a5, double* a6, double* a7);

void ARC_SPLINE_inter_2_monge_planes(ARC_SPLINE_monge_plane_s* a1,
                                     ARC_SPLINE_monge_plane_s* a2,
                                     double* a3,
                                     UGS::Math::Point3* a4,
                                     UGS::Math::Vector3* a5,
                                     int* a6)
{

    double v9 = sin(a3[1] * 0.01745329251994328);

    a4->x = 0.0;
    a4->y = 0.0;
    a4->z = 0.0;
    a5->x = 0.0;
    a5->y = 0.0;
    a5->z = 0.0;
    *a6 = 0;



    struct Bufs
    {
        UGS::Math::Vector3 n1;
        UGS::Math::Vector3 n2;
        UGS::Math::Point3  p2;
        UGS::Math::Point3  p1;
    } b;
    ARC_SPLINE_ask_pt_and_normal_of_monge_plane(a1, &b.p1, &b.n1);
    ARC_SPLINE_ask_pt_and_normal_of_monge_plane(a2, &b.p2, &b.n2);




    double cx = b.n2.z * b.n1.y - b.n2.y * b.n1.z;
    double cy = b.n1.z * b.n2.x - b.n1.x * b.n2.z;
    double cz = b.n1.x * b.n2.y - b.n1.y * b.n2.x;
    double norm = sqrt(cx * cx + cy * cy + cz * cz);


    if (v9 >= norm)
    {
        *a6 = 1;
    }
    else
    {
        int status;
        h634((const double*)&b.p1, (const double*)&b.n1, (const double*)&b.p2,
             (const double*)&b.n2, &status, (double*)a4, (double*)a5);
        if (status == 1)
        {
            *a6 = 1;
        }
        else if (status == 3)
        {
            *a6 = 2;
        }
    }
}
