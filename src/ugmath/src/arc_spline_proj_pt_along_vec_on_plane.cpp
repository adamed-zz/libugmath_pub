















#include <math.h>
#include <string.h>

namespace UGS
{
namespace Math
{
struct Point3
{
    double x;
    double y;
    double z;
};

struct Vector3
{
    double x;
    double y;
    double z;
};
}
}

void __cdecl ARC_SPLINE_proj_pt_along_vec_on_plane(UGS::Math::Point3* a1,
                                                   UGS::Math::Point3* a2,
                                                   UGS::Math::Vector3* a3,
                                                   UGS::Math::Vector3* a4,
                                                   double* a5,
                                                   UGS::Math::Point3* a6,
                                                   double* a7,
                                                   int* a8)
{
    *a8 = 0;
    const double num = (a1->y - a2->y) * a3->y
                     + (a1->x - a2->x) * a3->x
                     + (a1->z - a2->z) * a3->z;
    const double den = a3->y * a4->y
                     + a3->x * a4->x
                     + a3->z * a4->z;
    if (fabs(den) <= cos((90.0 - a5[1]) * 0.01745329251994328))
    {
        if (a5[0] >= fabs(num))
        {
            *a8 = -1;
            *a7 = 0.0;
            ((long long*)a6)[0] = ((const long long*)a1)[0];
            ((long long*)a6)[1] = ((const long long*)a1)[1];
            ((long long*)a6)[2] = ((const long long*)a1)[2];
        }
        else
        {
            *a8 = 1;
        }
    }
    else
    {
        const double t = -num / den;
        *a7 = t;
        const double ix = t * a4->x + a1->x;
        const double iy = t * a4->y + a1->y;
        const double iz = t * a4->z + a1->z;
        *(volatile double*)&a6->x = ix;
        *(volatile double*)&a6->y = iy;
        *(volatile double*)&a6->z = iz;
    }
}
